#!/usr/bin/python3
# codificao latin 1

import sys
import os
import subprocess
import argparse
import re

#PATH = os.path.dirname(os.path.abspath(__file__))

inOutDict = {};

#Função para mapear as entradas e saídas do código vhdl
def in_out(vhdl_file):
    #Abre arquivo vhdl e realiza a leitura.
    vhdl = open(vhdl_file, "r+").readlines()
    countlines = 0
    #executa o loop do arquivo para buscas das entradas e saídas
    while countlines < len(vhdl):
        #Identifica a entradas no código
        if ": in" in vhdl[countlines]:
            #Utiliza regex para identificar o nome da varivel de entrada
            matchIn = re.search(r'([A-Za-z_]+)?:',vhdl[countlines])
            if matchIn:
                inn = matchIn.group(0)
                inn = re.sub(r':',"", inn)
                #Adiciona a entrada ao dicionario inOutDict_
                inOutDict[inn] = "old["+str(inn)+"]"
        #indentifica as saídas no código
        if ": out" in vhdl[countlines]:
            #utiliza regex para indentificar o nome da variável de saída
            matchOut = re.search(r'([A-Za-z_]+)?:',vhdl[countlines])
            if matchOut:
                outt = matchOut.group(0)
                outt = re.sub(r':',"", outt)
                #acidiona a saída ao dicionário inOutDict
                inOutDict[outt] = "new["+str(outt)+"]"
        countlines += 1

#Função para tradução usando ferramenta V2C
def call_v2c(vhdl_file):
    #Executa a ferramenta V2C
    output = subprocess.getoutput('modules/v2c/v2c '+str(vhdl_file))
    print(output)
    #Busca o caminho path do arquivo
    arq = str(os .path.basename(vhdl_file))
    #Formata o caminho do arquivo C gerado do V2C
    cfile = str(os.path.dirname(vhdl_file))+'/'+str(arq.lower().replace(".vhd",".c"))
    #Retorna o caminho do arquivo
    return cfile

#Função de modificação do código para analise ESBMC
def new_c(cfile):
    #Abre arquivo C gerado pelo V2C.
    arquivo = open(cfile,"r+")
    #Salva o conteudo do arquivo em uma lista.
    linesC = arquivo.readlines()
    #print(*linesC)
    #Cria a lista textnewcfile.
    textnewcfile = []
    #Cria a lista asserts.
    asserts = []
    #Adiciona a string entre parentese na lista textnewcfile.
    textnewcfile.append("#include<stdio.h>\n")
    # Adiciona a string entre parentese na lista textnewcfile.
    textnewcfile.append("#define log_error(M, ...) fprintf(stderr,  M , __FILE__, __LINE__, ""##__VA_ARGS__)\n")
    # Adiciona a string entre parentese na lista textnewcfile.
    textnewcfile.append(" //Update to print the trace\n#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }\n")
    countlines = 0
    #Percorre o arquivo C em busca das assertivas.
    while countlines < len(linesC):
        #Caso encontre a tag inicial da assertiva, continua o loop até a tag final.
        if "@c2vhdl:ASSERT" in linesC[countlines]:
            while not "*@c2vhdl:END */" in linesC[countlines]:
                asserts.append(linesC[countlines])
                countlines += 1
            asserts.append(linesC[countlines])
            linesC.remove(str(linesC[countlines]))
            #Chama a função de tradução e após isso adiciona a assertiva traduzida ao código.
            textnewcfile.append(str(translate(asserts)+"\n"))
            asserts.clear()
        #Caso contrário, adiciona normalemnte as linhas de código a lista.
        else:
            textnewcfile.append(str(linesC[countlines]))
            countlines +=1

    arquivo.seek(0)
    arquivo.truncate()

    #print the new code
    for u in textnewcfile:
        arquivo.write(u)

#Função de tradução das assertivas
def translate(newblock):
    countlines = 1
    global aux
    while countlines < len(newblock):
        if "*assert" in newblock[countlines]:
            #Busca a condição da assertiva.
            matchassert1 = str(re.search(r'[()](.*)', newblock[countlines]).group(0))
            #Adiciona as variavéis traduzidas.
            for key in inOutDict:
                texto = key
                matchassert1 = re.sub(r'%s' %texto ,str(inOutDict[texto]),matchassert1)
            #Modifica o modelo para padrão da linguagem C.
            matchassert1 = re.sub(r'and',"&&",matchassert1)
            matchassert1 = re.sub(r'='," == ",matchassert1)
            if re.search(r'not',newblock[countlines]):
                aux = 0
            else:
                aux = 1
        if "*report" in newblock[countlines]:
            #Busca a mensagem de report gerada.
            matchassert2 = str(re.search(r'"(.*)"',newblock[countlines]).group(0))
        if "*severity" in newblock[countlines]:
            #Busca a gravidade do erro.
            matchassert3 = str(re.search(r'severity(.*)',newblock[countlines]).group(0))
        countlines += 1
    if aux == 0:
        #Adicona a assertiva ao texto caso apresente not
        textassert = "  //@c2vhdl:ASSERT - " + matchassert3 + "\n" + "    __MY_assert(!" + matchassert1 + "," + matchassert2 + ");\n"
    else:
        #Adiciona assetiva caso não presente not
        textassert = "  //@c2vhdl:ASSERT - " + matchassert3 + "\n" + "    __MY_assert(" + matchassert1 + "," + matchassert2 + ");\n"

    return textassert

#Função de analise das claims das assertivas
def esbmc_claims(claims, cfile):
    print("lista de claims encontradas: " + str(*claims))
    countlines1 = 0
    countlines2 = 0
    #Pela o nome da função devido a não existência do Main()
    namefunct = str(os.path.basename(cfile)).replace(".c","")
    esbmc_result = []
    while countlines1 < len(claims):
        print("Claim sendo executada: Claim " + str(claims[countlines1] + "\n"))
        #Comando para execução do unwind
        output = subprocess.getoutput('modules/esbmc/esbmc --64 --function '+ str(namefunct)+' '+str(cfile)+' --unwind 10 --no-pointer-check --no-div-by-zero-check --claim '+str(claims[countlines1]))
        output = output.split("\n")
        violated_line = len(output)+1
        while countlines2 < len(output):
            #Se houve alguma violação no código presente
            matchproperty = re.search(r'Violated', output[countlines2])
            if matchproperty:
                violated_line = countlines2
            if countlines2 >= violated_line:
                esbmc_result.append(output[countlines2])
            countlines2 += 1
        countlines1 += 1
        esbmc_result.append("\n")

    countlines1 = 0
    while countlines1 < len(esbmc_result):
        print(esbmc_result[countlines1])
        countlines1 += 1

#Função para analise e geração das claims
def call_esbmc(cfile):
    #lista de claims envolvendo assertivas
    claims = []
    countlines = 0
    #Comando para geração das claims no ESBMC
    output = subprocess.getoutput('modules/esbmc/esbmc --64 '+str(cfile)+' --show-claims').split("\n")
    print(subprocess.getoutput('modules/esbmc/esbmc --64 '+str(cfile)+' --show-claims'))
    while countlines < len(output):
        #identificar as claims geradas
        matchclaim = re.search(r'^Claim[ ]*([0-9]*)',output[countlines])
        if matchclaim:
            countlines += 2
            #identificar quais claims envolvem assertivas
            matchAssertion = re.search(r'assertion', str(output[countlines]))
            if matchAssertion:
                countlines += 1
                #Adiciona as claims das assertiva na lista
                claims.append(matchclaim.group(1))
        countlines += 1
    #Chama a função para aplicação do comando unwind a cada assertiva presente na lista
    esbmc_claims(claims,cfile)

#Função de funcionamento geral da ferramenta
def call_c2vhdl(vhdl_file):
    in_out(vhdl_file)
    cfile = call_v2c(vhdl_file)
    new_c(cfile)
    call_esbmc(cfile)

# __MAIN__
#Menu da ferramenta
if __name__ == "__main__":
    #Chamada do parser para criaçao dos argumentos do menu.
    parser = argparse.ArgumentParser(description='Run C2VHDL v1')
    #Argumento para exibir a versão da ferramenta.
    parser.add_argument('-v','--version', action='version', version="version 1")
    #Argumento para checagem dos programa passado para função.
    parser.add_argument(dest='inputVHDLProgram', metavar='file.vhdl', type=str,
                        help='the VHDL program file to be analyzed')

    #Salva os argumentao declarados.
    args = parser.parse_args()

    #Arquivo VHDL de entrada para analise.
    inputVHDLFile=""

    #Verificação do arquivo passado por argumento.
    if args.inputVHDLProgram:
        #Verifica se a função é um arquivo existente.
        if not os.path.isfile(args.inputVHDLProgram):
            print('Error: unable to open input file (%s)' % quote(args.inputVHDLProgram))
            parser.parse_args(['-h'])
            sys.exit()
        else:
            #Caso seja um arquivo válido, o caminho do arquivo é passado para variável inputVHDLFile.
            inputVHDLFile = os.path.abspath(args.inputVHDLProgram)

    call_c2vhdl(inputVHDLFile)
