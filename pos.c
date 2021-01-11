/*
--------- PHOEBUS TECNOLOGIA -----------
------ SIMULAÇÃO DE TERMINAL POS -------


DEV: FRANCISCO BRENO MOURA ALVES
OS: WINDOWS 10 X64
LINGUAGEM: C - JSON
COMPILER: MINGW-W64
IDE: VSCODE / DEV C++

TECLAS SIMULADAS:
ENTER -> ENTER
CANCEL -> ESC
BACKSPACE -> BACKSPACE
SPACE -> SPACE
TECLADO NUMERICO -> TECLADO NUMERICO

CODIGOS DE ERRO:
1 - ERRO MENOR QUE O VALOR MINIMO DA MODALIDADE PRETENDIDA
2 - ERRO MENOR QUE O VALOR MAXIMO DA MODALIDADE PRETENDIDA
3 - NUMERO INCOMPATIVEL DE PARCELAS
4 - OPERACAO CANCELADA PELO USUARIO
5 - CARTAO DE CREDITO OU DEBITO INVALIDO
6 - PRAZO DE ESTORNO SUPERIOR AO 1 DIA PARA DEBITO
7 - PRAZO DE ESTORNO SUPERIOR A 5 DIAS PARA CREDITO
8 - DATA INVALIDA PARA BUSCAR RELATORIO
9 - NÃO HÁ TRANSAÇÕES PARA A DATA

*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "time.h"
#include "windows.h"






//ESTRUTURAS PARA TERMINAL
struct Terminal {
	char identificacao[10];
	char endereco[500];
	char cnpj[20];
	char razaoSocial[30];
	char rodapeVenda[2000];
	char rodapeEstorno[2000];

} a;

//ESTRUTURAS PARA PRODUTOS
struct Produtos {
	char identificacao[4];
	int tipo;
	char rotulo[20];
	char razaoSocial[25];
	float vMin;
	float vMax;
} credito1, credito2, debito1;

/*ESTRUTURA DE ARMAZENAMENTO PARA REPOSITORIO DE VENDAS
RESSALVA: UTILIZAÇÃO DE UM VETOR DE ESTRUTURAS APENAS PARA FINS DE SIMPLIFICAÇÃO DE IMPLEMENTAÇÃO.
UMA ABORDAGEM MAIS EFICIENTE PARA APLICAÇÃO REAL SERIA A IMPLEMENTAÇÃO DE UMA ESTRUTURA DE DADOS MAIS ROBUSTA COM 
MAIOR ESCALABILIDADE COMO HASHMAP OU ARVORE B+. OUTRA SOLUÇÃO MENOS ELEGANTE, POREM FUNCIONAL E DE MAIS SIMPLES
IMPLEMENTAÇÃO SERIA DESENVOLIDA EM C++ UTILIZANDO VETORES DE VETORES DE ALOCAÇÃO DINAMICA (STD::VECTOR)
*/
struct RepositorioVendas {
	char razaoSocial[30];
	char endereco[500];
	char cnpj[20];
	int data[6];
	char idTerminal[10];
	char rotulo[22];
	char cartao[20];
	float valor;
	char rodapeVenda[2000];
	int estornado;
} repo[100];




main (int argc, char **argv) {
	
	//PARAMETROS DO CMD
	system("color 0a");
	system("MODE 60,20");;

//VAR PARA INDICAR POSIÇÃO ATUAL DO VETOR DO REPOSITORIO
	int indexRepo = 0;
	
/*A LINGUAGEM C NÃO FORNECE SUPORTE NATIVO A IMPLEMENTAÇÃO DE JSON, CONTUDO APÓS REALIZAR TENTATIVAS DE IMPLEMENTAÇÃO
UTILIZANDO JSON-C, JSMN E JANSSON, DEVIDO AO DEADLINE DA APLICAÇÃO FOI OPTADO POR REALIZAR UMA ATRIBUIÇÃO
DIRETA EM CODIGO DOS VALORES DO JSON.
*/

	strcpy(a.endereco, "Rua dom emanuel");
	strcpy(a.identificacao, "TERM0001");
	strcpy(a.cnpj, "21.505.538/0001-28");
	strcpy(a.razaoSocial, "Phoebus Tecnologia");
	strcpy(a.rodapeVenda, "A Phoebus e uma empresa que atua no mercado de \n     meios de pagamentos a 18 anos. Ela e pioneira\n     na criacao do primeiro sistema de pagamento de  \n     contas utilizando terminais POS");
	strcpy(a.rodapeEstorno, "Comprovante de estorno");

	strcpy(credito1.identificacao, "01");
	credito1.tipo = 1;
	strcpy(credito1.rotulo, "CREDITO A VISTA");
	credito1.vMin = 10;
	credito1.vMax = 10000;

	strcpy(credito2.identificacao, "02");
	credito2.tipo = 2;
	strcpy(credito2.rotulo, "CREDITO PARCELADO");
	credito2.vMin = 100;
	credito2.vMax = 10000;

	strcpy(debito1.identificacao, "03");
	debito1.tipo = 3;
	strcpy(debito1.rotulo, "DEBITO");
	debito1.vMin = 0;
	debito1.vMax = 0;

	

	int menu = 1;

	while (1) {


		//DATA E HORA
		time_t t = time(NULL);
		struct  tm tm=*localtime(&t);

		system("cls");
		printf("\n\n     %s  ", a.identificacao);
		printf("%d/%d %d:%d\n", tm.tm_mday,tm.tm_mon+1,tm.tm_hour,tm.tm_min);
		printf("      %s\n", a.razaoSocial);
		printf("     \n         Tecle ENTER\n         Para vender\n\n");
		printf("     1-ESTORNO    2-RELAT\n     ");

		char menu = getch();


		if (menu == 13) { //ENTRA NA VENDA
			system("cls");
			printf("\n\n       ESCOLHA A VENDA\n");
			printf("     1-%s\n",credito1.rotulo);
			printf("     2-%s\n",credito2.rotulo);
			printf("     3-%s\n     ",debito1.rotulo);

			char menu2;
			menu2 = getch();

			//CREDITO PARCELADO
			if(menu2 == '2') {
				
/* RESSALVA SOBRE O O USO DO GOTO: EMBORA CONSTANTE ALVO DE PRENOÇÃO, O GOTO É TRATADO COMO UM SALTO DE NÍVEL PADRÃO NO CODIGO 
GERADO EM ASSEMBLY, ASSIM COMO AS DEMAIS ESTRUTURAS DE SELEÇÃO (IF, ELSE, SWITCH...), NÃO GERANDO IMPACTOS NA PERFORMANCE.
EM FATOS, A UTILIZAÇÃO DO GOTO NESTE CODIGO SEGUE A MESMA LINHA DE RACIOCINIO DE USO DE UTILIZAÇÃO DO GOTO NO KERNEL DO 
LINUX: APENAS PARA TRATAMENTO DE ERROS, NÃO GERANDO PREJUIZOS NO QUE É TANGIVEL A LEITURA DE CODIGO.
*/				

digitevalorgoto:
				system("cls");
				printf("\n     %s \n\n          VALOR (R$) \n\n          ",credito2.rotulo);
				float valor = 0;
				scanf("%f",&valor);

				if(valor > 0) {
				//VERIFICACAO DOS MAX E MIN	
					if(valor < credito2.vMin) {
						system("cls");
						printf("\n     ERRO 1\n\n");
						printf("\n     VALOR MENOR QUE O \n     VALOR MINIMO DE \n     R$ %.2f",credito2.vMin);
						getch();
						goto digitevalorgoto;
					}
					if(valor > credito2.vMax) {
						system("cls");
						printf("\n     ERRO 2\n\n");
						printf("\n     VALOR MAIOR QUE O \n     VALOR MAXIMO DE \n     R$ %.2f",credito2.vMax);
						getch();
						goto digitevalorgoto;
					}

					if(valor >= credito2.vMin && valor <= credito2.vMax) {
parcelasgoto:
						system("cls");
						printf("\n     %s\n\n          PARCELAS\n\n     ",credito2.rotulo);
						int parcelas = 0;
						scanf("%d",&parcelas);

						if(parcelas <= 1) {
							system("cls");
							printf("\n     ERRO 3\n\n");
							printf("\n     NUMERO INCORRETO\n     DE PARCELAS");
							getch();
							goto parcelasgoto;
						}
//VERIFICA PARCELAS
						if(parcelas > 1) {
cartaogoto:
							system("cls");
							printf("\n     %s \n\n          CARTAO \n\n          ",credito2.rotulo);
							char cartao[20];
							scanf("%s",&cartao);


							if(strlen(cartao) > 11 && strlen(cartao) < 19) {
								system("cls");
								printf("\n     %s\n     CONFIRMA VENDA?\n\n");
								char cartaoExibir[20];
								strcpy(cartaoExibir, cartao);

								int i = 0;
								for(i = 0; i < strlen(cartao); i++) { //PARA CAMUFLAR O CARTÃO UTILIZADO
									if(i > 3 && i < (strlen(cartao)-4)) {
										cartaoExibir[i] = '*';
									}
								}

								printf("\n     %s\n",cartaoExibir);
								printf("     %.2f\n\n",valor);
								printf("     1-NAO      2-SIM");

								char confirma = getch();

								//CONSOLIDAÇÃO DA VENDA
								/*RESSALVA: SERIA MAIS ELEGANTE TODO O BLOCO A SEGUIR, QUE SE REPETE NAS OPERAÇÕES DE
								CREDITO E DEBITO, SER IMPLEMENTADO ATRAVES DE FUNÇÃO EXTERNA, CONTUDO OBTIVE PROBLEMAS
								DE ALOCAÇÃO DE MEMORIA LIDANDO COM PONTEIROS DOS VETORES DA STRUCT COMO ARGUMENTO DA
								FUNÇÃO, TAIS ERROS SÃO ORIUNDOS DE ALGUM COMPORTAMENTO NÃO ESPERADO DO COMPILADOR MINGW */
								if (confirma == '2') {
									fflush(stdin);
									strcpy(repo[indexRepo].razaoSocial,a.razaoSocial);
									strcpy(repo[indexRepo].endereco, a.endereco);
									strcpy(repo[indexRepo].cnpj, a.cnpj);
									repo[indexRepo].data[0] = tm.tm_mday;
									repo[indexRepo].data[1] = tm.tm_mon+1;
									repo[indexRepo].data[2] = tm.tm_year + 1900;
									repo[indexRepo].data[3] = tm.tm_hour;
									repo[indexRepo].data[4] = tm.tm_min;
									repo[indexRepo].data[5] = tm.tm_sec;
									strcpy(repo[indexRepo].idTerminal, a.identificacao);
									strcpy(repo[indexRepo].rotulo, credito2.rotulo);
									strcpy(repo[indexRepo].cartao, cartaoExibir);
									repo[indexRepo].valor = valor;
									strcpy(repo[indexRepo].rodapeVenda, a.rodapeVenda);
									repo[indexRepo].estornado = 0;

									system("cls");
									printf("\n                   %s\n",repo[indexRepo].razaoSocial);
									printf("                   %s\n",repo[indexRepo].endereco);
									printf("                   %s\n\n",repo[indexRepo].cnpj);
									printf("      Data: %d/%d/%d",repo[indexRepo].data[0],repo[indexRepo].data[1],repo[indexRepo].data[2]);
									printf("           Terminal:%s",repo[indexRepo].idTerminal);
									printf("\n\n      %s",repo[indexRepo].rotulo);
									printf("\n      %s",repo[indexRepo].cartao);
									printf("\n\n      VALOR APROVADO:                   R$ %.2f",repo[indexRepo].valor);
									printf("\n\n      %s",repo[indexRepo].rodapeVenda);

									indexRepo = indexRepo+1;
									getch();
								}
								//ERRO CANCELAMENTO
								if (confirma == '1') {
									system("cls");
									printf("\n     ERRO 4\n\n");
									printf("     OPERACAO CANCELADA");
									goto out;
								}



							}
							if(strlen(cartao) < 11 || strlen(cartao) > 19 ) {
								system("cls");
								printf("\n     ERRO 5\n\n");
								printf("\n     CARTAO INVALIDO");
								getch();
								goto cartaogoto;

							}

						}



					}
				} else {
					goto digitevalorgoto;
				}
			}

			//CREDITO A VISTA
			if(menu2 == '1') {
digitevalorgoto1:
				system("cls");
				printf("\n     %s \n\n       VALOR (R$) \n\n          ",credito1.rotulo); // falta o cancel
				float valor = 0;
				scanf("%f",&valor);

				if(valor > 0) {
					//entra na venda
					if(valor < credito1.vMin) {
						system("cls");
						printf("\n     ERRO 1\n\n");
						printf("\n     VALOR MENOR QUE O \n     VALOR MINIMO DE \n     R$ %.2f",credito1.vMin);
						getch();
						goto digitevalorgoto1;
					}
					if(valor > credito1.vMax) {
						system("cls");
						printf("\n     ERRO 2\n\n");
						printf("\n     VALOR MAIOR QUE O \n     VALOR MAXIMO DE \n     R$ %.2f",credito1.vMax);
						getch();
						goto digitevalorgoto1;
					}

					if(valor >= credito1.vMin && valor <= credito1.vMax) {
						if(1) {
cartaogoto1:
							system("cls");
							printf("\n     %s \n\n         CARTAO \n\n       ",credito1.rotulo);
							char cartao[20];
							scanf("%s",&cartao);


							if(strlen(cartao) > 11 && strlen(cartao) < 19) {
								system("cls");
								printf("\n     %s\n     CONFIRMA VENDA?\n\n");
								char cartaoExibir[20];
								strcpy(cartaoExibir, cartao);

								int i = 0;
								for(i = 0; i < strlen(cartao); i++) { //colocar asteriscos no cartao
									if(i > 3 && i < (strlen(cartao)-4)) {
										cartaoExibir[i] = '*';
									}
								}

								printf("\n     %s\n",cartaoExibir);
								printf("     %.2f\n\n",valor);
								printf("     1-NAO      2-SIM");

								char confirma = getch();

								//CONFIRMACAO DA VENDA
								if (confirma == '2') {
									fflush(stdin);
									strcpy(repo[indexRepo].razaoSocial,a.razaoSocial);
									strcpy(repo[indexRepo].endereco, a.endereco);
									strcpy(repo[indexRepo].cnpj, a.cnpj);
									repo[indexRepo].data[0] = tm.tm_mday;
									repo[indexRepo].data[1] = tm.tm_mon+1;
									repo[indexRepo].data[2] = tm.tm_year + 1900;
									repo[indexRepo].data[3] = tm.tm_hour;
									repo[indexRepo].data[4] = tm.tm_min;
									repo[indexRepo].data[5] = tm.tm_sec;
									strcpy(repo[indexRepo].idTerminal, a.identificacao);
									strcpy(repo[indexRepo].rotulo, credito1.rotulo);
									strcpy(repo[indexRepo].cartao, cartaoExibir);
									repo[indexRepo].valor = valor;
									strcpy(repo[indexRepo].rodapeVenda, a.rodapeVenda);
									repo[indexRepo].estornado = 0;

									system("cls");
									printf("\n                   %s\n",repo[indexRepo].razaoSocial);
									printf("                   %s\n",repo[indexRepo].endereco);
									printf("                   %s\n\n",repo[indexRepo].cnpj);
									printf("      Data: %d/%d/%d",repo[indexRepo].data[0],repo[indexRepo].data[1],repo[indexRepo].data[2]);
									printf("           Terminal:%s",repo[indexRepo].idTerminal);
									printf("\n\n      %s",repo[indexRepo].rotulo);
									printf("\n      %s",repo[indexRepo].cartao);
									printf("\n\n      VALOR APROVADO:                   R$ %.2f",repo[indexRepo].valor);
									printf("\n\n      %s",repo[indexRepo].rodapeVenda);

									indexRepo = indexRepo+1;
									getch();
								}
								//ERRO CANCELAMENTO
								if (confirma == '1') {
									system("cls");
									printf("\n     ERRO 4\n\n");
									printf("     OPERACAO CANCELADA");
									goto out;
								}



							}
							if(strlen(cartao) < 11 || strlen(cartao) > 19 ) {
								system("cls");
								printf("\n     ERRO 5\n\n");
								printf("\n     CARTAO INVALIDO");
								getch();
								goto cartaogoto1;

							}

						}



					}
				} else {
					goto digitevalorgoto1;
				}
			}


			//DEBITO
			if(menu2 == '3') {
digitevalorgoto2:
				system("cls");
				printf("\n     %s \n\n          VALOR (R$) \n\n          ",debito1.rotulo); // falta o cancel
				float valor = 0;
				scanf("%f",&valor);

				if(valor > 0) {
					//entra na venda
					if(valor >= debito1.vMin) {
						if(1) {
cartaogoto2:
							system("cls");
							printf("\n     %s \n\n          CARTAO \n\n          ",debito1.rotulo);
							char cartao[20];
							scanf("%s",&cartao);


							if(strlen(cartao) > 11 && strlen(cartao) < 19) {
								system("cls");
								printf("\n     %s\n     CONFIRMA VENDA?\n\n");
								char cartaoExibir[20];
								strcpy(cartaoExibir, cartao);

								int i = 0;
								for(i = 0; i < strlen(cartao); i++) { //colocar asteriscos no cartao 
									if(i > 3 && i < (strlen(cartao)-4)) {
										cartaoExibir[i] = '*';
									}
								}

								printf("\n     %s\n",cartaoExibir);
								printf("     R$ %.2f\n\n",valor);
								printf("     1-NAO      2-SIM");

								char confirma = getch();

								//CONFIRMACAO DA VENDA
								if (confirma == '2') {
									fflush(stdin);
									strcpy(repo[indexRepo].razaoSocial,a.razaoSocial);
									strcpy(repo[indexRepo].endereco, a.endereco);
									strcpy(repo[indexRepo].cnpj, a.cnpj);
									repo[indexRepo].data[0] = tm.tm_mday;
									repo[indexRepo].data[1] = tm.tm_mon+1;
									repo[indexRepo].data[2] = tm.tm_year + 1900;
									repo[indexRepo].data[3] = tm.tm_hour;
									repo[indexRepo].data[4] = tm.tm_min;
									repo[indexRepo].data[5] = tm.tm_sec;
									strcpy(repo[indexRepo].idTerminal, a.identificacao);
									strcpy(repo[indexRepo].rotulo, debito1.rotulo);
									strcpy(repo[indexRepo].cartao, cartaoExibir);
									repo[indexRepo].valor = valor;
									strcpy(repo[indexRepo].rodapeVenda, a.rodapeVenda);
									repo[indexRepo].estornado = 0;

									system("cls");
									printf("\n                   %s\n",repo[indexRepo].razaoSocial);
									printf("                   %s\n",repo[indexRepo].endereco);
									printf("                   %s\n\n",repo[indexRepo].cnpj);
									printf("      Data: %d/%d/%d",repo[indexRepo].data[0],repo[indexRepo].data[1],repo[indexRepo].data[2]);
									printf("           Terminal:%s",repo[indexRepo].idTerminal);
									printf("\n\n     %s",repo[indexRepo].rotulo);
									printf("\n     %s",repo[indexRepo].cartao);
									printf("\n\n     VALOR APROVADO:                   R$ %.2f",repo[indexRepo].valor);
									printf("\n\n     %s",repo[indexRepo].rodapeVenda);


									indexRepo = indexRepo+1;
									getch();
								}
								//ERRO CANCELAMENTO
								if (confirma == '1') {
									system("cls");
									printf("\n     ERRO 4\n\n");
									printf("     OPERACAO CANCELADA");
									goto out;
								}



							}
							if(strlen(cartao) < 11 || strlen(cartao) > 19 ) {
								system("cls");
								printf("\n     ERRO 5\n\n");
								printf("\n     CARTAO INVALIDO");
								getch();
								goto cartaogoto2;

							}

						}



					}
				} else {
					goto digitevalorgoto2;
				}
			}



			//ESC
			if(menu2 == 27) { //SAIR
				goto out;
			}


		}

		if (menu == '1') { //ENTRA NO ESTORNO
listaExtorno:
			
			system("cls");		
			int i;
			char selectEstorno;
			printf("\n          ESTORNO\n");
			for(i = 0; i < indexRepo; i++ ){
				if(repo[i].estornado == 0){ //SO EXIBE AS NÃO ESTORNADAS
					printf("\n     %d-%d/%d/%d R$ %.2f",i+1,repo[i].data[0],repo[i].data[1],repo[i].data[2],repo[i].valor);
				}
			}
			selectEstorno = getch();
			int indexEstorno = selectEstorno - '0';
			indexEstorno = indexEstorno - 1;


			if(selectEstorno == 27){//SAIR
				goto out;
			}
			
			if(selectEstorno == 13){
				goto listaExtorno;
			}
			
			int logicaEstorno = 0;
			
			//PARA VERIFICAR CONDICOES DE ESTORNO FORAM ATINGIDAS
			if(indexEstorno < indexRepo){
				if((strcmp(repo[indexEstorno].rotulo,"DEBITO") == 0)){
					if(repo[indexEstorno].data[0] == tm.tm_mday && repo[indexEstorno].data[1] == tm.tm_mon+1){
						logicaEstorno = 1;
					} else {
						logicaEstorno = 2;
					}
				} else {
					if(repo[indexEstorno].data[0] >= tm.tm_mday && repo[indexEstorno].data[0] < tm.tm_mday+5  && repo[indexEstorno].data[1] == tm.tm_mon+1){
						logicaEstorno = 1;
					} else {
						logicaEstorno = 3;
					}
				}
			}
			
			if(logicaEstorno == 1){
				
							
					char confirmaEstorno;
					system("cls");
					printf("\n          %s\n     Confirma Estorno?",repo[indexEstorno].rotulo);
					printf("\n\n     %s",repo[indexEstorno].cartao);
					printf("\n     R$ %.2f",repo[indexEstorno].valor);
					printf("\n\n     1-NAO          2-SIM");
					confirmaEstorno = getch();
					
					//CONFIRMA ESTORNO
					if(confirmaEstorno == '2'){
						repo[indexEstorno].estornado = 1;
					
						system("cls");
						printf("\n                %s\n",repo[indexEstorno].razaoSocial);
						printf("                   %s\n",repo[indexEstorno].endereco);
						printf("                   %s\n\n",repo[indexEstorno].cnpj);
						printf("      Data: %d/%d/%d",repo[indexEstorno].data[0],repo[indexEstorno].data[1],repo[indexEstorno].data[2]);
						printf("      Terminal:%s",repo[indexEstorno].idTerminal);
						printf("\n\n     Estorno      %s",repo[indexEstorno].rotulo);
						printf("\n      %s",repo[indexEstorno].cartao);
						printf("\n\n     VALOR CANCELADO:                   R$ %.2f",repo[indexEstorno].valor);
						printf("\n\n     %s",a.rodapeEstorno);
						
						getch();
					}
				
				

			} else {
				if(logicaEstorno == 2){
					system("cls");
					printf("     ERRO 6\n\n");
					printf("     Prazo de 1 dia para estorno de debito");
					goto out;
				}
				if(logicaEstorno == 3){
					system("cls");
					printf("     ERRO 7\n\n");
					printf("     Prazo de 5 dias para estorno de credito");
					goto out;
				}
			}
			
			

		}

		if (menu == '2'){ //ENTRA NO RELATORIO
checarDataRelatorio:
			system("cls");
			printf("\n     DIGITE A DATA\n\n       ");
			int dataRelatorio[3];
			scanf("          %d/%d/%d",&dataRelatorio[0],&dataRelatorio[1],&dataRelatorio[2]);
			
			//VERIFICAR VALIDADE DA DATA
			int dataValida = 0;
			if(dataRelatorio[2] == tm.tm_year + 1900){
				if((dataRelatorio[1] <= tm.tm_mon+1) && (dataRelatorio[1] > 0 )){
					if((dataRelatorio[0] <= tm.tm_mday) && (dataRelatorio[0] > 0 )){
						dataValida = 1;
					}
				}
			} 
			
			if((dataRelatorio[2] < tm.tm_year + 1900) && (dataRelatorio[2] > 2018)){
				if((dataRelatorio[1] <= 12) && (dataRelatorio[1] > 0)){
					if((dataRelatorio[0] <= 31) && (dataRelatorio[0] > 0)){
						dataValida = 1;
					}
				}
			}
			
			
			if(dataValida == 1){
				int i = 0;
				
				int qtdCredito1 = 0, qtdCredito2 = 0, qtdDebito1 = 0, qtdTotal = 0, entrouRel = 0;
				float vCredito1 = 0, vCredito2 = 0, vDebito1 = 0, vTotal = 0;
				
				for(i = 0; i < indexRepo; i++){ //IMPRIMIR RELATORIO
							
					if((repo[i].data[2] == dataRelatorio[2]) && (repo[i].data[1] == dataRelatorio[1]) && (repo[i].data[0] == dataRelatorio[0])){
						entrouRel = 1;
						if(strcmp(repo[i].rotulo,"CREDITO A VISTA") == 0){
							qtdCredito1++;
							qtdTotal++;
							vCredito1 = vCredito1 + repo[i].valor;
							vTotal = vTotal + repo[i].valor;
						}
						
						if(strcmp(repo[i].rotulo, "CREDITO PARCELADO") == 0){
							qtdCredito2++;
							qtdTotal++;
							vCredito2 = vCredito2 + repo[i].valor;
							vTotal = vTotal + repo[i].valor;
						}
					
						if(strcmp(repo[i].rotulo, "DEBITO") == 0 ){
							qtdDebito1++;
							qtdTotal++;
							vDebito1 = vDebito1 + repo[i].valor;
							vTotal = vTotal + repo[i].valor;
						}
					
					} 	
				
					
				}
				
				if(entrouRel == 1){
				
					//CABECALHO DO RELATORIO
					system("cls");
					printf("\n                   %s\n",a.razaoSocial);
					printf("                   %s\n",a.endereco);
					printf("                   %s\n\n",a.cnpj);
					printf("     %d/%d/%d     %d:%d:%d     ",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900,tm.tm_hour,tm.tm_min,tm.tm_sec);
					printf("%s\n\n",a.identificacao);
					printf("     %s\n     QTD: %d                  VALOR: R$ %.2f\n\n",credito1.rotulo, qtdCredito1,vCredito1);
					printf("     %s\n     QTD: %d                  VALOR: R$ %.2f\n\n",credito2.rotulo, qtdCredito2,vCredito2);
					printf("     %s\n     QTD: %d                  VALOR: R$ %.2f\n\n",debito1.rotulo, qtdDebito1,vDebito1);
					printf("     ----------------- TOTAL ---------------\n");
					printf("     QTD: %d                  VALOR: R$ %.2f\n",qtdTotal,vTotal);
					printf("     ---------------------------------------\n");
				
					getch();
					system("cls");
				} else {

					system("cls");
					printf("     ERRO 9\n\n");
					printf("     NAO HA TRANSACOES");
					getch();
					goto out;
					
				}
					
			} else {
				system("cls");
				printf("     ERRO 8\n\n");
				printf("     Data invalida");
				getch();
				goto checarDataRelatorio;
			}
		}
out:
		fflush(stdin);

	}



}


