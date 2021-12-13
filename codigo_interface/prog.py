import funcoes_aux as aux
import PySimpleGUI as sg   
import threading as th
import subprocess
import time 
import re  
import os

sg.ChangeLookAndFeel('LightGreen')      
sg.SetOptions(element_padding=(0, 0))      

    # ------ Menu Definition ------ #      
menu_def = [['Arquivo', ['Abrir', 'Salvar', 'Salvar em Novo']]]      

aneis_def = [
                [sg.T("Algoritmo:", size=(15,1)),sg.Radio("A1P", "RadioAneis", key="A1P", enable_events=True, default=True, size=(4,1)), sg.Radio("A1LSC", "RadioAneis", key="A1LSC", enable_events=True, size=(6,1)), sg.Radio("A1LCC", "RadioAneis", key="A1LCC", size=(6,1)), sg.Radio("A2P", "RadioAneis", key="A2P", size=(4,1)), sg.Radio("A2L", "RadioAneis", key="A2L", size=(4,1)), sg.Radio("A3", "RadioAneis", key="A3", size=(4,1))],
                [sg.T("Escrever Cores?", size=(15,1)), sg.Radio("Sim", "RCE", key="Sim", enable_events=True, size=(4,1)), sg.Radio("Não", "RCE", key="Nao", default=True, size=(4,1)), sg.T("| Número máximo de threads:", size=(26,1)), sg.In(key="NumThreads", default_text="8", enable_events=True, size=(6,1))],
                [sg.T("", size=(31,1)),sg.T(" Grão das Threads", size=(26,1)), sg.In(key="GraoThreads", default_text="40", enable_events=True, size=(6,1))],
                [sg.Button("Procurar aneis",auto_size_button=True), sg.Radio("A1C1", "RTIP", key="A1C1", default=True), sg.Radio("A2C2", "RTIP", key="A2C2"), sg.Radio("A3C3", "RTIP", key="A3C3")]
            ]

funcoes_def =   [
                    [sg.Button("Procurar todas juncoes", key='juncoes', auto_size_button=True)]
                ]
    # ------ GUI Defintion ------ #      
layout =    [      
                [sg.Menu(menu_def, )],      
                [sg.Multiline(size=(65, 20), key='Output')], 
                [sg.Frame(layout=aneis_def, title='Anéis')],
                [sg.T("")],
                [sg.Frame(layout=funcoes_def, title='Funções')]
            ]      

window = sg.Window("Program", layout, default_element_size=(12, 1), auto_size_text=False, auto_size_buttons=False,      
                       default_button_element_size=(12, 1))      

thread = None
filename = None
numThreads = "8"
grao = "40"
while True:      
    event, values = window.read()   
    if event == sg.WIN_CLOSED or event == 'Exit':      
        break

    if event == 'Abrir':
        try:
            filename = sg.popup_get_file('file to open', initial_folder="entrada", no_window=True)
            if filename:
                f = open(filename, "r")    
                window['Output'].update(value=f.read())
                f.close()
        except Exception as e:
            print(e)

    elif event == 'Salvar':
        if filename:
            try:
                f = open(filename, "w")
                f.write(window['Output'].get())
                f.close()
            except:
                print("Erro ao Salvar o arquivo")
    
    elif event == 'Salvar em Novo':
        filename = sg.popup_get_text('Type the new file name')
        if filename and filename != "":
            try:
                filename = "." + os.sep + "entrada" + os.sep + filename
                f = open(filename, 'w')
                f.write(window['Output'].get())
                f.close()
            except Exception as e:
                print(e)

    elif event == 'A1LSC':
        window['Nao'].update(value=True)

    elif event == "Sim":
        if window['A1LSC'].get():
            window['A1P'].update(value=True)

    elif event == "NumThreads":
        texto = window['NumThreads'].get()
        if bool(re.fullmatch("([0-9]+)", texto)):
            numThreads = texto
        elif texto != "":
            window['NumThreads'].update(value=numThreads)

    elif event == "GraoThreads":
        texto = window['GraoThreads'].get()
        if bool(re.fullmatch("([0-9]+)", texto)):
            grao = texto
        elif texto != "":
            window['GraoThreads'].update(value=grao)

    elif event == "Procurar aneis":
        caminho_entrada = "." + os.sep +'arquivos_prog' + os.sep + 'temp_0'
        try:
            f = open(caminho_entrada, 'w')
            f.write(window['Output'].get())
            f.close()
        except Exception as e:
            print(e)
            continue
        
        if not aux.verificar_entrada(caminho_entrada):
            sg.popup_error('Erro na entrada')
            continue
        else:
            if thread:
                if thread.is_alive():
                    sg.popup_error('Uma funcionalidade já está em execução')
                    continue

            print("Procurando aneis interface")
            #1 = A1C1, 2 = A2C2, 3 = A3C3
            tipo_anel = '3' if window['A3C3'].get() else '2' if window['A2C2'].get() else '1'   
            #0 = A1P, 1 = A1LSC, 2 = A1LCC, 3 = A2P, 4 = A2L, 5 = A3
            algoritmo = '0' if window['A1P'].get() else '1' if window['A1LSC'].get() else '2' if window['A1LCC'].get() else '3' if window['A2P'].get() else '4' if window['A2L'].get() else '5'
            escreve_cores = '1' if window['Sim'].get() else '0'
            max_threads = window['NumThreads'].get()


            if filename:
                filename_mod = filename.split(os.sep)
                filename_mod = filename_mod[len(filename_mod) - 1].split('.')
                filename_mod = filename_mod[0]
            else:
                filename_mod = "auto"
            caminho_programa = "." + os.sep +'arquivos_prog' + os.sep + 'a.out'
            caminho_destino='aneis' + os.sep + filename_mod + "_aneis.txt"
                
            args = [caminho_programa, caminho_entrada, "0", tipo_anel, algoritmo, max_threads, grao, escreve_cores, filename_mod, caminho_destino]
            thread = aux.executar_c_plusplus(args)
            
    elif event == 'juncoes':
        caminho_entrada = "." + os.sep +'arquivos_prog' + os.sep + 'temp_1'
        try:
            f = open(caminho_entrada, 'w')
            f.write(window['Output'].get())
            f.close()
        except Exception as e:
            print(e)
            continue

        if not aux.verificar_entrada(caminho_entrada):
            sg.popup_error('Erro na entrada')
            continue
        else:
            if thread:
                if thread.is_alive():
                    sg.popup_error('Uma funcionalidade já está em execução')
                    continue

            print("Procurando pelas juncoes")
            if filename:
                filename_mod = filename.split(os.sep)
                filename_mod = filename_mod[len(filename_mod) - 1].split('.')
                filename_mod = filename_mod[0]
            else:
                filename_mod = "auto"
            caminho_programa = "." + os.sep +'arquivos_prog' + os.sep + 'a.out'
            caminho_destino='aneis' + os.sep + filename_mod + "_juncoes.txt"

            args = [caminho_programa, caminho_entrada, '1', filename_mod, caminho_destino]
            thread = aux.executar_c_plusplus(args)