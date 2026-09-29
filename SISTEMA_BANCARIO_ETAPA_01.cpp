/******************************************************************************
Trabalho – Implementação de um Sistema de
Registro e Gestão de Contas Bancárias (ETAPA 1) – VERSÃO 4 (COMENTADA)
(até 5 clientes, CPF numérico, senha forte, suporte a acentos)
*******************************************************************************/

#include <iostream>   // Biblioteca de entrada e saída (cin, cout, endl)
#include <string>     // Biblioteca para trabalhar com textos (string)
#include <limits>     // Fornece numeric_limits, usado para limpar o buffer do teclado
#include <clocale>    // Fornece setlocale, usado para exibir acentos corretamente
#include <cctype>     // Fornece isdigit, usado para verificar se um caractere é número
using namespace std;  // Permite usar cout, cin, string etc. sem escrever "std::" antes

int main() {  // Função principal: é onde o programa começa a ser executado

	setlocale(LC_ALL, "Portuguese"); // Configura o idioma para português (acentos no terminal do Windows)

	const int MAX_CLIENTES = 5; // Constante com o limite máximo de clientes cadastrados

	// VARIÁVEIS OBRIGATÓRIAS (agora vetores: uma posição por cliente)
	int numeroConta[MAX_CLIENTES];     // Vetor com o número da conta de cada cliente
	string nomeCliente[MAX_CLIENTES];  // Vetor com o nome de cada titular
	string senhaConta[MAX_CLIENTES];   // Vetor com a senha de cada titular
	string cpf[MAX_CLIENTES];          // Vetor com o CPF de cada titular
	int tipoConta[MAX_CLIENTES];       // Vetor com o tipo da conta: 1 = Corrente; 2 = Poupança
	double saldo[MAX_CLIENTES];        // Vetor com o saldo atual de cada conta
	bool contaAtiva[MAX_CLIENTES];     // Vetor com a situação da conta: true = ativa, false = desativada

	// VARIÁVEIS EXTRAS
	int opcao = 0;             // Guarda a opção escolhida no menu
	int contadorCliente = 0;   // Quantidade de clientes cadastrados (também é a próxima posição livre)
	int alterarConta = 0;      // Guarda a escolha de ativar (1) ou desativar (0) a conta
	int numeroDigitado = 0;    // Guarda o número da conta informado no login
	string senhaDigitada;      // Guarda a senha informada no login
	string cpfDigitado;        // Guarda o CPF informado durante o cadastro
	int indice = -1;           // Posição da conta encontrada no vetor (-1 = não encontrada)
	bool cpfValido = false;    // Indica se o CPF digitado passou nas validações
	string senhaNova;          // Guarda a senha digitada no cadastro, antes de ser aprovada
	bool temMaiuscula = false; // Indica se a senha tem pelo menos 1 letra maiúscula
	bool temEspecial = false;  // Indica se a senha tem pelo menos 1 caractere especial
	bool senhaForte = false;   // Indica se a senha cumpriu todas as regras
	const string especiais = "!@#$%&*()-_+=[]{};:,.<>?/\\|~^'\"`"; // Lista dos caracteres considerados especiais

	// Inicializa os vetores
	for (int i = 0; i < MAX_CLIENTES; i++) { // Percorre todas as posições, de 0 até 4
		numeroConta[i] = 0;                  // Zera o número da conta
		tipoConta[i] = 0;                    // Zera o tipo da conta (0 = ainda não definido)
		saldo[i] = 0.0;                      // Zera o saldo
		contaAtiva[i] = false;               // Marca a posição como conta inativa
	}                                        // Fim do for de inicialização

	do { // Início do laço do menu: repete até o usuário escolher sair
		cout << "\n=============================================\n"; // Linha decorativa do topo do menu
		cout << "------------- BANCO PREMIUM -------------\n";       // Título do banco
		cout << "=============================================\n\n"; // Linha decorativa abaixo do título
		cout << "Selecione uma opção válida do menu (1 a 6):\n\n";    // Instrução para o usuário
		cout << "1 - Cadastrar conta (" << contadorCliente << "/" << MAX_CLIENTES << ")" << endl; // Opção 1, mostrando quantas vagas foram usadas
		cout << "2 - Consultar conta" << endl;           // Opção 2 do menu
		cout << "3 - Verificar saldo" << endl;           // Opção 3 do menu
		cout << "4 - Alterar tipo da conta" << endl;     // Opção 4 do menu
		cout << "5 - Ativar/Desativar conta" << endl;    // Opção 5 do menu
		cout << "6 - Sair\n" << endl;                    // Opção 6 do menu
		cout << "Opção selecionada: ";                   // Pede a escolha do usuário
		cin >> opcao;                                    // Lê a opção digitada

		// Se o usuário digitou letras, limpa o erro para não travar o programa
		if (cin.fail()) {   // Verifica se a leitura falhou (ex.: digitou letra no lugar de número)
			cin.clear();    // Remove o estado de erro do cin
			opcao = 0;      // Define uma opção inválida para cair no "default" do switch
		}                   // Fim do if
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta o resto da linha digitada (inclusive o Enter)

		switch (opcao) { // Escolhe o que fazer de acordo com a opção digitada

		case 1: // Opção 1: cadastrar conta
			cout << "\n1 - Cadastrar conta" << endl; // Exibe o título da opção

			if (contadorCliente >= MAX_CLIENTES) { // Verifica se já foram cadastrados 5 clientes
				cout << "Limite de " << MAX_CLIENTES << " clientes atingido." << endl; // Informa que não há mais vagas
				break;                              // Sai do switch e volta ao menu
			}                                       // Fim do if do limite

			do { // Repete enquanto o nome estiver vazio
				cout << "Nome do cliente: ";                       // Pede o nome
				getline(cin, nomeCliente[contadorCliente]);        // Lê a linha inteira (permite nomes com espaço)
			} while (nomeCliente[contadorCliente].empty());        // Repete se o usuário só apertou Enter

			do { // Repete até o CPF ser válido
				cout << "Insira o CPF (11 dígitos, somente números): "; // Pede o CPF
				cin >> cpfDigitado;                                     // Lê o CPF digitado

				// Deve ter 11 caracteres e todos devem ser dígitos
				cpfValido = (cpfDigitado.length() == 11);               // Começa válido só se tiver exatamente 11 caracteres
				for (size_t i = 0; i < cpfDigitado.length(); i++) {     // Percorre cada caractere do CPF
					if (!isdigit((unsigned char)cpfDigitado[i])) {      // Se o caractere NÃO for um número...
						cpfValido = false;                              // ...o CPF é considerado inválido
					}                                                   // Fim do if do dígito
				}                                                       // Fim do for dos caracteres

				if (!cpfValido) { // Se o CPF já foi reprovado
					cout << "CPF inválido. Digite exatamente 11 números." << endl; // Avisa o erro ao usuário
				} else { // Se o formato está correto, verifica se já existe
					// Não permite CPF repetido
					for (int j = 0; j < contadorCliente; j++) { // Percorre os clientes já cadastrados
						if (cpf[j] == cpfDigitado) {            // Se algum CPF cadastrado for igual ao digitado...
							cpfValido = false;                  // ...marca como inválido
							cout << "CPF já cadastrado." << endl; // Avisa que o CPF está repetido
						}                                       // Fim do if de CPF igual
					}                                           // Fim do for de clientes
				}                                               // Fim do if/else de validação
			} while (!cpfValido);                               // Repete enquanto o CPF não for válido
			cpf[contadorCliente] = cpfDigitado;                 // Guarda o CPF válido na posição do novo cliente

			do { // Repete até a senha ser forte
				cout << "Crie uma senha forte (máximo 8 caracteres, com 1 letra maiúscula e 1 caractere especial): "; // Pede a senha e explica as regras
				cin >> senhaNova;                                       // Lê a senha digitada
				temMaiuscula = false;                                   // Zera o indicador de letra maiúscula
				temEspecial = false;                                    // Zera o indicador de caractere especial
				for (size_t i = 0; i < senhaNova.length(); i++) {       // Percorre cada caractere da senha
					if (senhaNova[i] >= 'A' && senhaNova[i] <= 'Z') {   // Se o caractere for letra maiúscula (A a Z)...
						temMaiuscula = true;                            // ...marca que existe maiúscula
					}                                                   // Fim do if da maiúscula
					if (especiais.find(senhaNova[i]) != string::npos) { // Se o caractere estiver na lista de especiais...
						temEspecial = true;                             // ...marca que existe caractere especial
					}                                                   // Fim do if do especial
				}                                                       // Fim do for dos caracteres
				senhaForte = (senhaNova.length() <= 8 && temMaiuscula && temEspecial); // Só é forte se cumprir as três regras
				if (senhaNova.length() > 8) cout << "A senha deve ter no máximo 8 caracteres." << endl; // Avisa se passou de 8 caracteres
				if (!temMaiuscula) cout << "A senha precisa de pelo menos 1 letra maiúscula." << endl;  // Avisa se faltar maiúscula
				if (!temEspecial) cout << "A senha precisa de pelo menos 1 caractere especial (ex.: ! @ # $ %)." << endl; // Avisa se faltar especial
			} while (!senhaForte);                                      // Repete enquanto a senha não for forte
			senhaConta[contadorCliente] = senhaNova;                    // Guarda a senha aprovada na posição do novo cliente

			do { // Repete até o saldo ser válido
				cout << "Insira o saldo inicial: ";                     // Pede o saldo inicial
				cin >> saldo[contadorCliente];                          // Lê o saldo
				if (cin.fail()) {                                       // Se o usuário digitou algo que não é número...
					cin.clear();                                        // ...limpa o estado de erro
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ...e descarta o que foi digitado
					saldo[contadorCliente] = -1;                        // ...define valor negativo para forçar nova tentativa
				}                                                       // Fim do if de erro de leitura
				if (saldo[contadorCliente] < 0) cout << "Valor inválido." << endl; // Avisa se o saldo for negativo
			} while (saldo[contadorCliente] < 0);                       // Repete enquanto o saldo for negativo

			do { // Repete até o tipo de conta ser 1 ou 2
				cout << "Insira o tipo de conta (1 = Corrente; 2 = Poupança): "; // Pede o tipo da conta
				cin >> tipoConta[contadorCliente];                      // Lê o tipo digitado
				if (cin.fail()) {                                       // Se digitou algo que não é número...
					cin.clear();                                        // ...limpa o estado de erro
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ...descarta o que foi digitado
					tipoConta[contadorCliente] = 0;                     // ...define valor inválido para repetir a pergunta
				}                                                       // Fim do if de erro de leitura
			} while (tipoConta[contadorCliente] != 1 && tipoConta[contadorCliente] != 2); // Repete enquanto não for 1 nem 2

			numeroConta[contadorCliente] = 1001 + contadorCliente; // Gera o número da conta (1001, 1002, ...)
			contaAtiva[contadorCliente] = true;                    // A conta nasce ativa

			cout << "\nA conta foi registrada.\n";                                   // Confirma o cadastro
			cout << "Bem-vindo(a), " << nomeCliente[contadorCliente] << "!" << endl; // Dá as boas-vindas ao cliente
			cout << "O número da sua conta é: " << numeroConta[contadorCliente] << endl; // Informa o número da conta gerado

			contadorCliente++; // Aumenta a quantidade de clientes cadastrados
			break;             // Sai do switch e volta ao menu

		case 2: // Opção 2: consultar conta
			cout << "\n2 - Consultar conta" << endl; // Exibe o título da opção
			if (contadorCliente == 0) {              // Verifica se ainda não há nenhuma conta
				cout << "Nenhuma conta cadastrada." << endl; // Informa que não há contas
				break;                               // Sai do switch e volta ao menu
			}                                        // Fim do if
			cout << "Insira o número da conta: ";    // Pede o número da conta
			cin >> numeroDigitado;                   // Lê o número digitado
			if (cin.fail()) { cin.clear(); numeroDigitado = -1; } // Se não for número, limpa o erro e usa -1 (conta inexistente)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta o resto da linha digitada
			cout << "Insira a senha: ";              // Pede a senha
			cin >> senhaDigitada;                    // Lê a senha digitada

			indice = -1;                                 // Começa considerando que a conta não foi encontrada
			for (int i = 0; i < contadorCliente; i++) {  // Percorre as contas cadastradas
				if (numeroConta[i] == numeroDigitado) indice = i; // Se o número bater, guarda a posição
			}                                            // Fim do for de busca

			if (indice == -1 || senhaConta[indice] != senhaDigitada) { // Conta não encontrada OU senha diferente
				cout << "Número da conta ou senha incorretos." << endl; // Avisa o erro de login
			} else if (!contaAtiva[indice]) {            // Login correto, mas a conta está desativada
				cout << "Conta desativada." << endl;     // Avisa que a conta está desativada
			} else {                                     // Login correto e conta ativa
				cout << "Nome: " << nomeCliente[indice] << endl;            // Mostra o nome do titular
				cout << "CPF: " << cpf[indice] << endl;                     // Mostra o CPF do titular
				cout << "Número da conta: " << numeroConta[indice] << endl; // Mostra o número da conta
				cout << "Tipo: " << (tipoConta[indice] == 1 ? "Corrente" : "Poupança") << endl; // Mostra o tipo (operador ternário)
				cout << "Situação: Ativa" << endl;                           // Mostra a situação da conta
			}                                            // Fim do if/else
			break;                                       // Sai do switch e volta ao menu

		case 3: // Opção 3: verificar saldo
			cout << "\n3 - Verificar saldo" << endl; // Exibe o título da opção
			if (contadorCliente == 0) {              // Verifica se ainda não há nenhuma conta
				cout << "Nenhuma conta cadastrada." << endl; // Informa que não há contas
				break;                               // Sai do switch e volta ao menu
			}                                        // Fim do if
			cout << "Insira o número da conta: ";    // Pede o número da conta
			cin >> numeroDigitado;                   // Lê o número digitado
			if (cin.fail()) { cin.clear(); numeroDigitado = -1; } // Se não for número, limpa o erro e usa -1 (conta inexistente)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta o resto da linha digitada
			cout << "Insira a senha: ";              // Pede a senha
			cin >> senhaDigitada;                    // Lê a senha digitada

			indice = -1;                                 // Começa considerando que a conta não foi encontrada
			for (int i = 0; i < contadorCliente; i++) {  // Percorre as contas cadastradas
				if (numeroConta[i] == numeroDigitado) indice = i; // Se o número bater, guarda a posição
			}                                            // Fim do for de busca

			if (indice == -1 || senhaConta[indice] != senhaDigitada) { // Conta não encontrada OU senha diferente
				cout << "Número da conta ou senha incorretos." << endl; // Avisa o erro de login
			} else if (!contaAtiva[indice]) {            // Login correto, mas a conta está desativada
				cout << "Conta desativada." << endl;     // Avisa que a conta está desativada
			} else {                                     // Login correto e conta ativa
				cout << "Saldo atual: R$ " << saldo[indice] << endl; // Mostra o saldo da conta
			}                                            // Fim do if/else
			break;                                       // Sai do switch e volta ao menu

		case 4: // Opção 4: alterar tipo da conta
			cout << "\n4 - Alterar tipo da conta" << endl; // Exibe o título da opção
			if (contadorCliente == 0) {              // Verifica se ainda não há nenhuma conta
				cout << "Nenhuma conta cadastrada." << endl; // Informa que não há contas
				break;                               // Sai do switch e volta ao menu
			}                                        // Fim do if
			cout << "Insira o número da conta: ";    // Pede o número da conta
			cin >> numeroDigitado;                   // Lê o número digitado
			if (cin.fail()) { cin.clear(); numeroDigitado = -1; } // Se não for número, limpa o erro e usa -1 (conta inexistente)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta o resto da linha digitada
			cout << "Insira a senha: ";              // Pede a senha
			cin >> senhaDigitada;                    // Lê a senha digitada

			indice = -1;                                 // Começa considerando que a conta não foi encontrada
			for (int i = 0; i < contadorCliente; i++) {  // Percorre as contas cadastradas
				if (numeroConta[i] == numeroDigitado) indice = i; // Se o número bater, guarda a posição
			}                                            // Fim do for de busca

			if (indice == -1 || senhaConta[indice] != senhaDigitada) { // Conta não encontrada OU senha diferente
				cout << "Número da conta ou senha incorretos." << endl; // Avisa o erro de login
			} else if (!contaAtiva[indice]) {            // Login correto, mas a conta está desativada
				cout << "Conta desativada." << endl;     // Avisa que a conta está desativada
			} else {                                     // Login correto e conta ativa
				do { // Repete até o novo tipo ser 1 ou 2
					cout << "Digite 1 para Corrente ou 2 para Poupança: "; // Pede o novo tipo
					cin >> tipoConta[indice];                              // Lê e já grava o novo tipo na conta
					if (cin.fail()) {                                      // Se digitou algo que não é número...
						cin.clear();                                       // ...limpa o estado de erro
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ...descarta o que foi digitado
						tipoConta[indice] = 0;                             // ...define valor inválido para repetir a pergunta
					}                                                      // Fim do if de erro de leitura
				} while (tipoConta[indice] != 1 && tipoConta[indice] != 2); // Repete enquanto não for 1 nem 2
				cout << "Tipo da conta alterado para "                     // Início da mensagem de confirmação
				     << (tipoConta[indice] == 1 ? "Corrente" : "Poupança") << "." << endl; // Completa a mensagem com o novo tipo
			}                                            // Fim do if/else
			break;                                       // Sai do switch e volta ao menu

		case 5: // Opção 5: ativar/desativar conta
			cout << "\n5 - Ativar/Desativar conta" << endl; // Exibe o título da opção
			if (contadorCliente == 0) {              // Verifica se ainda não há nenhuma conta
				cout << "Nenhuma conta cadastrada." << endl; // Informa que não há contas
				break;                               // Sai do switch e volta ao menu
			}                                        // Fim do if
			cout << "Insira o número da conta: ";    // Pede o número da conta
			cin >> numeroDigitado;                   // Lê o número digitado
			if (cin.fail()) { cin.clear(); numeroDigitado = -1; } // Se não for número, limpa o erro e usa -1 (conta inexistente)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta o resto da linha digitada
			cout << "Insira a senha: ";              // Pede a senha
			cin >> senhaDigitada;                    // Lê a senha digitada

			indice = -1;                                 // Começa considerando que a conta não foi encontrada
			for (int i = 0; i < contadorCliente; i++) {  // Percorre as contas cadastradas
				if (numeroConta[i] == numeroDigitado) indice = i; // Se o número bater, guarda a posição
			}                                            // Fim do for de busca

			if (indice == -1 || senhaConta[indice] != senhaDigitada) { // Conta não encontrada OU senha diferente
				cout << "Número da conta ou senha incorretos." << endl; // Avisa o erro de login
			} else {                                     // Login correto (aqui a conta pode estar ativa ou não)
				do { // Repete até o usuário digitar 1 ou 0
					cout << "Digite 1 para ativar a conta e 0 para desativar: "; // Pede a escolha
					cin >> alterarConta;                                         // Lê a escolha digitada
					if (cin.fail()) {                                            // Se digitou algo que não é número...
						cin.clear();                                             // ...limpa o estado de erro
						cin.ignore(numeric_limits<streamsize>::max(), '\n');      // ...descarta o que foi digitado
						alterarConta = -1;                                       // ...define valor inválido para repetir a pergunta
					}                                                            // Fim do if de erro de leitura
				} while (alterarConta != 1 && alterarConta != 0);                // Repete enquanto não for 1 nem 0

				contaAtiva[indice] = (alterarConta == 1); // true se digitou 1 (ativar); false se digitou 0 (desativar)
				cout << "A conta foi " << (contaAtiva[indice] ? "ativada" : "desativada") // Escolhe a palavra conforme o novo estado
				     << " com sucesso." << endl;                                         // Completa a mensagem de confirmação
			}                                            // Fim do if/else
			break;                                       // Sai do switch e volta ao menu

		case 6: // Opção 6: sair
			cout << "\n6 - Sair" << endl;             // Exibe o título da opção
			cout << "Operação finalizada!" << endl;   // Mensagem de despedida
			break;                                    // Sai do switch (o laço do-while encerra em seguida)

		default: // Qualquer outro valor
			cout << "\nOpção inválida!" << endl; // Avisa que a opção não existe
		}                                        // Fim do switch

	} while (opcao != 6); // Repete o menu enquanto o usuário não escolher 6 (Sair)

	return 0; // Encerra o programa informando que terminou sem erros
}             // Fim da função main
