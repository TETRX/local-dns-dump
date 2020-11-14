from subprocess import Popen,PIPE

def get_command_output(command):
    pid = Popen(command, stdout=PIPE)
    s = pid.communicate()[0]
    return s

def get_command_error(command):
    pid = Popen(command, stderr=PIPE)
    s = pid.communicate()[1]
    return s


def arpsend():
    line=get_command_error(["arpsend", "-e"]).decode("utf-8")
    return line

print(arpsend())
