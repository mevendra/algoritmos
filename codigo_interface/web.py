from flask import Flask, render_template, request, session,redirect
from werkzeug.utils import secure_filename, send_from_directory

import funcoes_aux as aux
import threading as th
import time
import os

app = Flask(__name__)
app.secret_key = 'a'
app.config['UPLOAD_FOLDER'] = 'arquivos_prog'
app.config['DOWNLOAD_FOLDER'] = 'aneis'
app.config['SESSION_PERMANENT'] = False
app.config['PERMANENT_SESSION_LIFETIME'] = 3600   #3600

caminho_programa = os.path.join(app.config['UPLOAD_FOLDER'], "a.out")
i = 1

NUMERO_MAXIMO_THREADS=2
NUMERO_MAXIMO_THREADS_PROGRAMA_C=8
TEMPO_TIMEOUT_SEMAPHORE=15
TEMPO_TIMEOUT_THREAD=10
TEMPO_SALVAR_ARQUIVOS=app.config['PERMANENT_SESSION_LIFETIME'] + 10

semaphore = th.Semaphore(NUMERO_MAXIMO_THREADS)

@app.route('/')
def novo_anel():
    global i
    if 'id' not in session:
        local_i = i
        i = i + 1
        session['id'] = str(local_i)
        timer = th.Timer(TEMPO_SALVAR_ARQUIVOS, apagar_arquivos, args=(session['id']))
        #timer = th.Timer(2, apagar_arquivos, args=(session['id']))
        timer.start()

    return render_template('index.html', titulo='MaqPar')

@app.route('/teste')
def teste():    
    adquiriu = semaphore.acquire(timeout=TEMPO_TIMEOUT_SEMAPHORE)
    if not adquiriu:
        return render_template('erro.html', titulo='Timeout!', tipo_erro='O servidor está sobrecarregado!')
    time.sleep(40)
    semaphore.release()
    return redirect('/')

def ler_arquivo(arquivo):
    i = session['id']
    if not arquivo:
        if 'caminho_arquivo' not in session:
            return render_template('erro.html', titulo='Erro!', tipo_erro='Arquivo não definido!')
        elif not os.path.isfile(session['caminho_arquivo']):
            return render_template('erro.html', titulo='Erro!', tipo_erro='Arquivo não encontrado!')
    else:
        try:
            sec_filename = secure_filename(arquivo.filename)
            caminho_arquivo = os.path.join(app.config['UPLOAD_FOLDER'], sec_filename + i)
            arquivo.save(caminho_arquivo)

            filename_mod = sec_filename.split(os.sep)
            filename_mod = filename_mod[len(filename_mod) - 1].split('.')
            filename_mod = filename_mod[0]

            if 'caminho_arquivo' in session:
                if session['caminho_arquivo'] != caminho_arquivo:
                    if os.path.isfile(session['caminho_arquivo']):
                        os.remove(session['caminho_arquivo'])

            session['caminho_arquivo'] = caminho_arquivo
            session['nome_rede'] = filename_mod
        except:
            return render_template('erro.html', titulo='Erro!', tipo_erro= 'Erro na leitura do arquivo pelo servidor!')
    
    return 'ok'

@app.route('/encontrar_aneis', methods=['POST',])
def encontrar_aneis():
    print('encontrar_aneis')
    i = session['id']

    arquivo = request.files['filename']
    resp = ler_arquivo(arquivo)
    if resp != 'ok':
        return resp

    caminho_arquivo = session['caminho_arquivo']
    if 'nome_rede' not in session:
        filename_mod = i
    else:
        filename_mod = session['nome_rede']

    if not aux.verificar_entrada(caminho_arquivo):
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro na sintaxe do arquivo!')

    nome_novo_arq = filename_mod + "_" + i + '_aneis.txt'
    caminho_destino = os.path.join(app.config['DOWNLOAD_FOLDER'], nome_novo_arq)

    tipo_anel = request.form['radio_anel']
    algoritmo = request.form['radio_algo']
    max_threads = request.form['max_threads']
    if not max_threads.isdigit():
        return render_template('erro.html', titulo='Leitura de dados!', tipo_erro='O número de threads não é um inteiro!')
    elif int(max_threads) < 0:
        return render_template('erro.html', titulo='Leitura de dados!', tipo_erro='O número de threads é menor que 0!')
    elif int(max_threads) > NUMERO_MAXIMO_THREADS_PROGRAMA_C:
        return render_template('erro.html', titulo='Leitura de dados!', tipo_erro='O número de threads é muito alto! O máximo é ' + str(NUMERO_MAXIMO_THREADS_PROGRAMA_C))
    
    grao = request.form['grao']
    if not grao.isdigit():
        return render_template('erro.html', titulo='Leitura de dados!', tipo_erro='O grão não é um inteiro!')
    elif int(grao) < 0:
        return render_template('erro.html', titulo='Leitura de dados!', tipo_erro='O grão é menor que 0!')

    escreve_cores = request.form['radio_cor']

    coloracao = request.form['radio_cores']

    args = [caminho_programa, caminho_arquivo, "0", tipo_anel, algoritmo, max_threads, grao, escreve_cores, filename_mod, caminho_destino, coloracao]

    adquiriu = semaphore.acquire(timeout=TEMPO_TIMEOUT_SEMAPHORE)
    if not adquiriu:
        return render_template('erro.html', titulo='Timeout!', tipo_erro='O servidor está sobrecarregado!')

    try:
        #Resetando timer
        thread = aux.executar_c_plusplus(args)
        thread.join(timeout=TEMPO_TIMEOUT_THREAD)
        if thread.is_alive():     #Timeout
            return render_template('erro.html', titulo='Timeout!', tipo_erro='A busca demorou mais que o tempo máximo!')

    except:
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro na thread!')
    finally:
        semaphore.release()

    result = thread.get_result()

    if result == 0:
        session['caminho_destino'] = caminho_destino
        session['nome_arquivo'] = nome_novo_arq
        return render_template('download.html', titulo='Anéis Encontrados!')
    elif result == 1:
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro na execução do programa (Leitura da entrada)!')
    elif result == 2:
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro na execução do programa!')
    else:
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro inesperado no programa!')

@app.route('/encontrar_juncoes', methods=['POST',])
def encontrar_juncoes():
    i = session['id']

    arquivo = request.files['filename']
    resp = ler_arquivo(arquivo)
    if resp != 'ok':
        return resp

    caminho_arquivo = session['caminho_arquivo']
    if 'nome_rede' not in session:
        filename_mod = i
    else:
        filename_mod = session['nome_rede']

    if not aux.verificar_entrada(caminho_arquivo):
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro na sintaxe do arquivo!')

    adquiriu = semaphore.acquire(timeout=TEMPO_TIMEOUT_SEMAPHORE)
    if not adquiriu:
        return render_template('erro.html', titulo='Timeout!', tipo_erro='O servidor está sobrecarregado!')

    nome_novo_arq = filename_mod + "_" + i + '_juncoes.txt'
    caminho_destino = os.path.join(app.config['DOWNLOAD_FOLDER'], nome_novo_arq)

    args = [caminho_programa, caminho_arquivo, "1", filename_mod, caminho_destino]

    try:
        thread = aux.executar_c_plusplus(args)
        thread.join(timeout=TEMPO_TIMEOUT_THREAD)
        if thread.is_alive():     #Timeout
            return render_template('erro.html', titulo='Timeout!', tipo_erro='A busca demorou mais que o tempo máximo!')
    except:
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro na thread!')
    finally:
        semaphore.release()
    result = thread.get_result()

    semaphore.release()

    if result == 0:
        session['caminho_destino'] = caminho_destino
        session['nome_arquivo'] = nome_novo_arq
        return render_template('download.html', titulo='Juncões Encontradas!')
    elif result == 1:
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro na execução do programa (Leitura da entrada)!')
    elif result == 2:
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro na execução do programa!')
    else:
        return render_template('erro.html', titulo='Erro!', tipo_erro='Erro inesperado no programa!')
            

@app.route('/getArquivo', methods=['POST',])
def getArquivo():
    print('GetArquivo')
    if 'caminho_destino' not in session or 'nome_arquivo' not in session:
        return render_template('erro.html', titulo='Erro no nome do arquivo!')
    elif not os.path.isfile(session['caminho_destino']):
        return render_template('erro.html', titulo='Erro, arquivo não encontrado!')
    
    nome_arquivo = session['nome_arquivo']
    return send_from_directory(app.config['DOWNLOAD_FOLDER'], nome_arquivo, as_attachment=True, environ=request.environ)

def apagar_arquivos(idUsuario):
    print("Apagando os arquivos do usuario: ", idUsuario)

    for file in os.listdir(app.config['DOWNLOAD_FOLDER']):
        if file.endswith("_" + idUsuario + "_aneis.txt") or file.endswith("_" + idUsuario + "_juncoes.txt"):
            os.remove(os.path.join(app.config['DOWNLOAD_FOLDER'], file))

    for file in os.listdir(app.config['UPLOAD_FOLDER']):
        if file.endswith(idUsuario):
            os.remove(os.path.join(app.config['UPLOAD_FOLDER'], file))


app.run(host='localhost', port = 8080, debug=True)
#app.run(host='localhost', port = 8080)


print("Fim")