//autor eugenio pozzobon
//matricula 201810349
//data 12/02/2021

/*
O objetivo deste trabalho é implementar um micro shell para sistemas Linux chamado msh. O shell deve pedir comandos do usuário com o caracter: msh>

O Micro Shell deve suportar apenas comandos. Os comandos a ser desenvolvimentos:

	dir: chama o comando listar (/bin/ls).
	pausa: tem como argumento um número que é o tempo segundos que deve esperar antes de continuar. Deve-se utilizar a função sleep().
	executa: recebe como argumento o caminho completo do programa a ser executado. Os comandos serão simples, ou seja, eles não tem argumentos adicionais.
	sair: termina o programa com a função exit().

As principais funções de sistema necessárias são fork(), execve() e wait(). A chamada fork() simplesmente cria um clone do processo atual e ambos (pai e filho) contiuam a execução a partir da chamada de sistema. execve() carrega um novo programa no espaço de memória do processo, e wait() espera o término de um processo filho previamente criado.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv){

	pid_t pid;     // PID do processo
	char *args[2]; // argumentos do comando para execv
	char *cmd; //comando do usuÃ¡rio para o shell
	char entrada[100]; //entrada raw do usuario

	
	while(1){ // enquanto nÃ£o sair do shell
		printf("msh>");
		fgets(entrada, 100, stdin); //pega o comando dado
		
		entrada[strlen(entrada)-1] = '\0'; //remove o '\n'
				
		cmd = strtok(entrada, " " ); //divide o comando para pegar sÃ³ a parte que importa
		
		if(strncmp(cmd, "dir" ,100) == 0){ //comando dir
			//printf("pÃ³s ls \n");
			pid = fork();
			//printf("pÃ³s fork \n");
			switch(pid){
				case -1:
				  printf("Erro!\n");
				  exit(EXIT_FAILURE);
				case 0:
				  // Sou o filho
				  args[0] = "/usr/bin/ls"; // comando ls
				  args[1] = NULL;
				  args[2] = NULL;
				  execve(args[0], args, NULL);
				  break;
				default:
				// Eu sou pai: espera o filho 
				wait(NULL);
				break;
			}
		}else if(strncmp(cmd, "pausa" ,100) == 0){ //comando pausa
			cmd = strtok(NULL, " " ); //pega o tempo passado pelo usuÃ¡rio
			
			if(cmd == NULL){ //verificaÃ§Ã£o de erro
				continue;
			}
			
			printf("pausando por %s segundos \n", cmd);
			
		 	sleep(atoi(cmd));
		 	

		}else if(strncmp(cmd, "sair" ,100) == 0){//comando sair do loop
			break;
		}else if(strncmp(cmd, "executa" ,100) == 0){//comando executa
			cmd = strtok(NULL, " ");
			pid = fork();
			switch(pid){
				case -1:
				  printf("Erro!\n");
				  exit(EXIT_FAILURE);
				case 0:
				  // Sou o filho
				  args[0] = cmd; // comando passado pela funÃ§Ã£o
				  args[1] = NULL;
				  args[2] = NULL;
				  execve(args[0], args, NULL);
				  break;
				default:
				// Eu sou pai: espera o filho 
				wait(NULL);
				break;
			}			
			
		}else{//identifica comando nÃ£o encontrado
			printf("Comando nÃ£o encontrado\n");
		}  

	}

  return 0;
}
