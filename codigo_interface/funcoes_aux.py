import threading as th
import subprocess
import time 
import re  

class Thread(th.Thread):
    def __init__(self, group=None, target=None, name=None, args=(), kwargs={}, *, daemon=None):
        super(Thread, self).__init__(group=group, target=target, name=name, daemon=daemon)
        self.target = target
        self.args = args
        self.kwargs = kwargs

    def run(self):
        self.retorno = self.target(self.args)

    def get_result(self):
        return self.retorno

def verificar_entrada(filename): 
    match = "(\*[A-Z][a-z]*[A-Z]*\n)(\*Vertices\n)([0-9]+ [0-9]+ (triangle|ellipse)\n)*(\*Edges\n)([0-9]+ [0-9]+\n)*(\*Arcs\n)([0-9]+ [0-9]+\n)*([0-9]+ [0-9]+)?"
    f = open(filename, 'r')
    conteudo = f.read()
    f.close()
    return bool(re.match(match, conteudo))

#args = ['NOME_ARQUIVO', 'ARG1', 'ARG2' ...]
def executar_c_plusplus(args):
    #thread = th.Thread(target=subprocess.call, args=(args, ))
    thread = Thread(target=subprocess.call, args=args)
    thread.start()

    return thread