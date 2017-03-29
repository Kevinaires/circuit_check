#!/usr/bin/env python
# codificao latin 1

import sys
import os
import commands
import argparse
import string
import re

#file = sys.argv[1]
#TODO: obter caminho absoluto para o arquivos utilizados
PATH = os.path.dirname(os.path.abspath(__file__))

#TODO: funcoes

def alterar_tipo(vhdl_file):
    arq = str(os.path.basename(vhdl_file))
    cfile = arq.lower()
    return cfile.replace(".vhd",".c")

def path_cprogram(vhdl_file):
    return os.path.dirname(vhdl_file)

def call_v2c(vhdl_file):
    output = commands.getoutput('modules/v2c/v2c '+str(vhdl_file))
    print output

def call_esbmc(cfile):
    output = commands.getoutput('modules/esbmc/esbmc ')

def translate(newblock):
    countlines = 1
    newline=[]
    global aux
    while countlines < len(newblock):
        if "*assert" in newblock[countlines]:
            matchassert1 = re.search(r'[()](.*)', newblock[countlines])
            print newblock[countlines]
            if re.search(r'not',newblock[countlines]):
                aux = 0
            else:
                aux = 1
        if "*report" in newblock[countlines]:
            matchassert2 = re.search(r'"(.*)"',newblock[countlines])
        if "*severity" in newblock[countlines]:
            matchassert3 = re.search(r'severity(.*)',newblock[countlines])
        countlines += 1
    if aux == 0:
        # translate assert matchassert.group(0)
        textassert = "//@c2vhdl:ASSERT - " + str(matchassert3.group(0))+ "\n" + "__MY_assert(!" + str(matchassert1.group(0)) + "," + str(matchassert2.group(0)) + ")"
    else:
        textassert = "//@c2vhdl:ASSERT - " + str(matchassert3.group(0))+ "\n" + "__MY_assert(" + str(matchassert1.group(0)) + "," + str(matchassert2.group(0)) + ")"

    return textassert

def new_c(cfile):
    arquivo = open(cfile,"r+")
    linesC = arquivo.readlines()
    textnewcfile = []
    newfileC = []
    textnewcfile.append("#define log_error(M, ...) fprintf(stderr, ""\n "" M ""\n \n"", __FILE__, __LINE__, ""##__VA_ARGS__)\n\nvoid")
    textnewcfile.append("#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); } //Update to print the trace")

    countlines = 0
    while countlines < len(linesC):
        if "*@c2vhdl:ASSERT" in linesC[countlines]:
            match1 = re.search(r'(/\*)',linesC[countlines],re.IGNORECASE)
            if not match1:
                linesC[countlines] = re.sub(r'(\*)',"/*",linesC[countlines])
            textnewcfile.append(linesC[countlines])
            countlines+=1
        if "*@c2vhdl:END" in linesC[countlines]:
            match2 = re.search(r'(\*/)',linesC[countlines],re.IGNORECASE)
            if not match2:
                linesC[countlines] = re.sub(r'(END\n)',"END */\n",linesC[countlines])
            textnewcfile.append(linesC[countlines])
            textnewcfile.append("\n")
            countlines+=1
        else:
            textnewcfile.append(linesC[countlines])
            countlines+=1

    countlines2 = 0
    while countlines2 < len(textnewcfile):
        getblockassert = []
        flagsearch = False
        if "@c2vhdl:ASSERT" in textnewcfile[countlines2]:
            while not flagsearch:
                getblockassert.append(textnewcfile[countlines2])
                newfileC.append(textnewcfile[countlines2])
                matchblock = re.search(r'@c2vhdl:END \*/',textnewcfile[countlines2])
                if not matchblock:
                    countlines2+=1
                else:
                    flagsearch = True
            newfileC.append("\n")
            newfileC.append(translate(getblockassert))
        newfileC.append(textnewcfile[countlines2])
        countlines2+=1

    arquivo.seek(0)
    arquivo.truncate()

    #print the new code
    for u in newfileC:
        arquivo.write(u)

    for u in newfileC:
        print u

def call_c2vhdl(vhdl_file):
    call_v2c(vhdl_file)
    path_cfile = path_cprogram(vhdl_file)
    nome_arquivo = alterar_tipo(vhdl_file)
    cfile = path_cfile+'/'+nome_arquivo
    new_c(cfile)
    #call_esbmc(cfile)
    #print cfile

    # analisar resultado
    # imprimir resultados


#outputList = output.split('\n')
#TODO: pegar apenas o caminho do codigo c gerado - REGEX

#TODO: com o caminho do codigo c gerado chamar o ESBMC

# __MAIN__
#TODO: Criar um menu para a ferramenta - map2check.py
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Run C2VHDL v1')
    parser.add_argument('-v','--version', action='version' , version="version 1")
    parser.add_argument(dest='inputVHDLProgram', metavar='file.vhdl', type=str,
                        help='the VHDL program file to be analyzed')

    args = parser.parse_args()
    ############# Check options in the args
    ### vars to save data option
    inputVHDLFile=""
    inputCFile=""

    if args.inputVHDLProgram:
        if not os.path.isfile(args.inputVHDLProgram):
            print('Error: unable to open input file (%s)' % quote(args.inputVHDLProgram))
            parser.parse_args(['-h'])
            sys.exit()
        else:
            inputVHDLFile = os.path.abspath(args.inputVHDLProgram)

    # Run transformation
    call_c2vhdl(inputVHDLFile)
