/* match.c        *
 * Public Domain  *
 * Author Unknown */

static unsigned char upper[256], lower[256];

#define case_map(c) upper[(c) & 0xff]
#define to_up(c)    upper[(c) & 0xff]

static int init=0;

static void init_match()
{
  int c;
  for (c = 0; c < sizeof(upper); c++) upper[c] = lower[c] = c;
  for (c = 'a'; c <= 'z';        c++) upper[c] = c - 'a' + 'A';
  for (c = 'A'; c <= 'Z';        c++) lower[c] = c - 'A' + 'a';
  init=1;
}


static int recmatch(unsigned char *p, unsigned char *s)
/*unsigned char *p;       sh pattern to match */
/*unsigned char *s;       string to match it to */
/* Recursively compare the sh pattern p with the string s and return 1 if
   they match, and 0 or 2 if they don't or if there is a syntax error in the
   pattern.  This routine recurses on itself no deeper than the number of
   characters in the pattern. */
{
  unsigned int c;       /* pattern char or start of range in [-] loop */

  /* Get first character, the pattern for new recmatch calls follows */
  c = *p++;

  /* If that was the end of the pattern, match if string empty too */
  if (c == 0)
    return *s == 0;

  /* '?' (or '%') matches any character (but not an empty string) */
  if (c == '?')
    return *s ? recmatch(p, s + 1) : 0;

  /* '*' matches any number of characters, including zero */
  if (c == '*')
  {
    if (*p == 0)
      return 1;
    for (; *s; s++)
      if ((c = recmatch(p, s)) != 0)
        return c;
    return 2;           /* 2 means give up--shmatch will return false */
  }

  /* Parse and process the list of characters and ranges in brackets */
  if (c == '[')
  {
    int e;              /* flag true if next char to be taken literally */
    unsigned char *q;   /* pointer to end of [-] group */
    int r;              /* flag true to match anything but the range */

    if (*s == 0)                        /* need a character to match */
      return 0;
    p += (r = (*p == '!' || *p == '^')); /* see if reverse */
    for (q = p, e = 0; *q; q++)         /* find closing bracket */
      if (e)
        e = 0;
      else
        if (*q == '\\')
          e = 1;
        else if (*q == ']')
          break;
    if (*q != ']')                      /* nothing matches if bad syntax */
      return 0;
    for (c = 0, e = *p == '-'; p < q; p++)      /* go through the list */
    {
      if (e == 0 && *p == '\\')         /* set escape flag if \ */
        e = 1;
      else if (e == 0 && *p == '-')     /* set start of range if - */
        c = *(p-1);
      else
      {
        unsigned char cc = case_map(*s);
        if (*(p+1) != '-')
          for (c = c ? c : *p; c <= *p; c++)    /* compare range */
            if (case_map(c) == cc)
              return r ? 0 : recmatch(q + 1, s + 1);
        c = e = 0;                      /* clear range, escape flags */
      }
    }
    return r ? recmatch(q + 1, s + 1) : 0;      /* bracket match failed */
  }

  /* If escape ('\'), just compare next character */
  if (c == '\\')
    if ((c = *p++) == 0)                /* if \ at end, then syntax error */
      return 0;

  /* Just a character--compare it */
  return case_map(c) == case_map(*s) ? recmatch(p, ++s) : 0;
}

int match(char *p, char *s)
/*char *p;                sh pattern to match */
/*char *s;                string to match it to */
/* Compare the sh pattern p with the string s and return true if they match,
   false if they don't or if there is a syntax error in the pattern. */
{
  if (!init) init_match();
  return recmatch((unsigned char *) p, (unsigned char *) s) == 1;
}

/* End of match.c */
