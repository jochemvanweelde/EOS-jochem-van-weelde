#include "shell.hh"
#include <fstream>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
using namespace std;

int main()
{ string input;

  ifstream myfile("opties.txt");
  string prompt;
  int teller = 0;
while(teller < 9){
	string huidig;
	getline (myfile,huidig);
	assert(!cin.eof());
	if(huidig.find("end") == 0) { break; }
	prompt.append(huidig);
	prompt.append(" \n");
	teller++;
}

  while(true)
  { cout << prompt << endl;                   // Print het prompt
    getline(cin, input);         // Lees een regel
    if (input == "new_file") new_file();   // Kies de functie
    else if (input == "ls") list();        //   op basis van
    else if (input == "src") src();        //   de invoer
    else if (input == "find") find();
    else if (input == "python") python();
    else if (input == "exit") return 0;
    else if (input == "quit") return 0;
    else if (input == "error") return 1;

    if (cin.eof()) return 0; } }      // EOF is een exit

void new_file() // ToDo: Implementeer volgens specificatie.
{ cout << "We gaan een nieuw bestand maken. \nHet eerste wat we nodig hebben is een naam van het bestand. \nGeef nu een naam van het nieuwe bestand: ";
string bestandsnaam;
string tekst;
getline(cin,bestandsnaam);
cout << bestandsnaam << endl;
ofstream bestand (bestandsnaam + ".txt");
cout << "Het bestand is aangemaakt!\nNu gaan we door naar tekst(na 1 regel op enter klikken) die je graag in het bestand wilt zetten.\nVul nu je tekst in: ";
getline(cin,tekst);
bestand << tekst << "\n";
while(true){
	cout << "Vul nu de volgende regel in of typ KLAAR als je klaar bent:\n";
	getline(cin,tekst);
	if(tekst == "KLAAR"){ break; }
	bestand << tekst << "\n";
}

}

void list() // ToDo: Implementeer volgens specificatie.
{
char * ls_args[] = { "/bin/ls" , "-la", NULL };
int status;
pid_t c_pid, pid;
c_pid = fork();
if (c_pid == 0){ //Dit is de child
	execv(ls_args[0], ls_args);
}else if (c_pid > 0){ //Dit is de parent
	if( (pid = wait(&status)) < 0){
		perror("wait");
		_exit(1);
	}	
}else{ // Error, fork heeft gefaald.
	perror("fork failed");
	_exit(1);
}
}

void find() // ToDo: Implementeer volgens specificatie.
{ 
string zoekwoord;
cout << "Je kan nu gaan zoeken naar een woord(en) in bepaalde files in directory ~/Downloads/V1EOS-practica-master/1_os_level \nNaar welke naam wil je zoeken:  ";
getline(cin,zoekwoord);
pid_t pid;
int status, fd[2], ret;

ret = pipe(fd);
if(ret == -1){
	perror("pipe");
	exit(1);
}

pid = fork();
if (pid == 0){ //Dit is de child1
	char * find_args[] = { "/usr/bin/find", "./" , NULL };
	close(fd[0]);
	cout << " Test" << endl << endl;
	dup2(fd[1], STDOUT_FILENO);
	execv(find_args[0], find_args);
}
pid = fork();
if(pid == 0){
	char * grep_args[] = {"/bin/grep", (char*)zoekwoord.c_str(), NULL};
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execv(grep_args[0],grep_args);
}
close(fd[1]);
close(fd[0]);
waitpid(-1, &status, 0);
waitpid(-1, &status, 0);
}

void python() // ToDo: Implementeer volgens specificatie.
{ 
char * python_args[] = { "/usr/bin/python" , NULL, NULL };
int status;
pid_t c_pid, pid;
c_pid = fork();
if (c_pid == 0){ //Dit is de child
	execv(python_args[0], python_args);
}else if (c_pid > 0){ //Dit is de parent
	if( (pid = wait(&status)) < 0){
		perror("wait");
		_exit(1);
	}	
}else{ // Error, fork heeft gefaald.
	perror("fork failed");
	_exit(1);
}
 }

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    cout << byte; }                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
