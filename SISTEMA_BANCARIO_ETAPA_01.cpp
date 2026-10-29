/******************************************************************************
Trabalho – Implementação de um Sistema de
Registro e Gestão de Contas Bancárias (ETAPA 1)
Yan Moura Lima - 28195
*******************************************************************************/

#include <iostream>   // Biblioteca de entrada e saída (cin, cout, endl)
#include <string>     // Biblioteca para trabalhar com textos (string)
using namespace std;  // Permite usar cout, cin, string etc. sem escrever "std::" antes

int main() {  // Função principal: é onde o programa começa a ser executado

	// VARIÁVEIS OBRIGATÓRIAS
	int numeroConta = 0;      // Número da conta (gerado no cadastro)
	string nomeCliente;       // Nome do titular
	string senhaConta;        // Senha do titular (guardada no cadastro e só usada para comparar)
	string cpf;               // CPF do titular
	int tipoConta = 0;        // Tipo da conta: 1 = Corrente; 2 = Poupança
	double saldo = 0.0;       // Saldo atual
	bool contaAtiva = false;  // Situação da conta: true = ativa, false = desativada

	// VARIÁVEIS EXTRAS
	int opcao = 0;            // Guarda a opção escolhida no menu
	int contadorCliente = 0;  // Quantidade de clientes cadastrados (0 = nenhum; 1 = já existe um cliente)
	int alterarConta = 0;     // Guarda a escolha de ativar (1) ou desativar (0) a conta
	int numeroDigitado = 0;   // Guarda o número da conta informado no login
	string senhaDigitada;     // Guarda a senha informada no login

	do { // Início do laço do menu: repete até o usuário escolher sair
		cout << "\n=============================================\n"; // Linha decorativa do topo do menu
		cout << "------------- BANCO PREMIUM -------------\n";       // Título do banco
		cout << "=============================================\n\n"; // Linha decorativa abaixo do título
		cout << "Selecione uma opção válida do menu (1 a 6):\n\n";    // Instrução para o usuário
		cout << "1 - Cadastrar conta" << endl;           // Opção 1 do menu
		cout << "2 - Consultar conta" << endl;           // Opção 2 do menu
		cout << "3 - Verificar saldo" << endl;           // Opção 3 do menu
		cout << "4 - Alterar tipo da conta" << endl;     // Opção 4 do menu
		cout << "5 - Ativar/Desativar conta" << endl;    // Opção 5 do menu
		cout << "6 - Sair\n" << endl;                    // Opção 6 do menu
		cout << "Opção selecionada: ";                   // Pede a escolha do usuário
		cin >> opcao;                                    // Lê a opção digitada
		cin.ignore(1000, '\n');                          // Descarta o resto da linha (o Enter), para o getline do cadastro funcionar

		switch (opcao) { // Escolhe o que fazer de acordo com a opção digitada

		case 1: // Opção 1: cadastrar conta
			cout << "\n1 - Cadastrar conta" << endl; // Exibe o título da opção

			if (contadorCliente >= 1) { // Verifica se já existe um cliente cadastrado
				cout << "Já existe uma conta cadastrada. Só é permitido 1 cliente." << endl; // Informa que não é possível cadastrar outro
				break;                  // Sai do switch e volta ao menu
			}                           // Fim do if do limite

			do { // Repete enquanto o nome estiver vazio
				cout << "Nome do cliente: ";   // Pede o nome
				getline(cin, nomeCliente);     // Lê a linha inteira (permite nomes com espaço)
			} while (nomeCliente.empty());     // Repete se o usuário só apertou Enter

			do { // Repete até o CPF ter 11 caracteres
				cout << "Insira o CPF (11 dígitos): ";   // Pede o CPF
				cin >> cpf;                              // Lê o CPF digitado
				if (cpf.length() != 11) cout << "CPF inválido. Digite exatamente 11 dígitos." << endl; // Avisa se não tiver 11 caracteres
			} while (cpf.length() != 11);                // Repete enquanto o CPF não tiver 11 caracteres

			do { // Repete até a senha ter exatamente 8 caracteres
				cout << "Crie uma senha de 8 caracteres: ";   // Pede a senha
				cin >> senhaConta;                            // Lê e guarda a senha do cliente
				if (senhaConta.length() != 8) cout << "A senha deve ter exatamente 8 caracteres." << endl; // Avisa se não tiver 8 caracteres
			} while (senhaConta.length() != 8);               // Repete enquanto a senha não tiver 8 caracteres

			do { // Repete até o saldo ser válido
				cout << "Insira o saldo inicial: ";           // Pede o saldo inicial
				cin >> saldo;                                 // Lê o saldo
				if (saldo < 0) cout << "Valor inválido." << endl; // Avisa se o saldo for negativo
			} while (saldo < 0);                              // Repete enquanto o saldo for negativo

			do { // Repete até o tipo de conta ser 1 ou 2
				cout << "Insira o tipo de conta (1 = Corrente; 2 = Poupança): "; // Pede o tipo da conta
				cin >> tipoConta;                             // Lê o tipo digitado
			} while (tipoConta != 1 && tipoConta != 2);       // Repete enquanto não for 1 nem 2

			numeroConta = 1001;   // Define o número da conta do único cliente
			contaAtiva = true;    // A conta nasce ativa
			contadorCliente = 1;  // Registra que já existe um cliente cadastrado

			cout << "\nA conta foi registrada.\n";                  // Confirma o cadastro
			cout << "Bem-vindo(a), " << nomeCliente << "!" << endl; // Dá as boas-vindas ao cliente
			cout << "O número da sua conta é: " << numeroConta << endl; // Informa o número da conta
			break;                                                  // Sai do switch e volta ao menu

		case 2: // Opção 2: consultar conta
			cout << "\n2 - Consultar conta" << endl; // Exibe o título da opção
			if (contadorCliente == 0) {              // Verifica se ainda não há nenhuma conta
				cout << "Nenhuma conta cadastrada." << endl; // Informa que não há conta
				break;                               // Sai do switch e volta ao menu
			}                                        // Fim do if
			cout << "Insira o número da conta: ";    // Pede o número da conta
			cin >> numeroDigitado;                   // Lê o número digitado
			cout << "Insira a senha: ";              // Pede a senha
			cin >> senhaDigitada;                    // Lê a senha digitada

			if (numeroDigitado != numeroConta || senhaDigitada != senhaConta) { // Número da conta OU senha não conferem
				cout << "Número da conta ou senha incorretos." << endl;         // Avisa o erro de login
			} else if (!contaAtiva) {                // Login correto, mas a conta está desativada
				cout << "Conta desativada." << endl; // Avisa que a conta está desativada
			} else {                                 // Login correto e conta ativa
				cout << "Nome: " << nomeCliente << endl;            // Mostra o nome do titular
				cout << "CPF: " << cpf << endl;                     // Mostra o CPF do titular
				cout << "Número da conta: " << numeroConta << endl; // Mostra o número da conta
				cout << "Tipo: " << (tipoConta == 1 ? "Corrente" : "Poupança") << endl; // Mostra o tipo (operador ternário)
				cout << "Situação: Ativa" << endl;                  // Mostra a situação da conta
			}                                        // Fim do if/else
			break;                                   // Sai do switch e volta ao menu

		case 3: // Opção 3: verificar saldo
			cout << "\n3 - Verificar saldo" << endl; // Exibe o título da opção
			if (contadorCliente == 0) {              // Verifica se ainda não há nenhuma conta
				cout << "Nenhuma conta cadastrada." << endl; // Informa que não há conta
				break;                               // Sai do switch e volta ao menu
			}                                        // Fim do if
			cout << "Insira o número da conta: ";    // Pede o número da conta
			cin >> numeroDigitado;                   // Lê o número digitado
			cout << "Insira a senha: ";              // Pede a senha
			cin >> senhaDigitada;                    // Lê a senha digitada

			if (numeroDigitado != numeroConta || senhaDigitada != senhaConta) { // Número da conta OU senha não conferem
				cout << "Número da conta ou senha incorretos." << endl;         // Avisa o erro de login
			} else if (!contaAtiva) {                // Login correto, mas a conta está desativada
				cout << "Conta desativada." << endl; // Avisa que a conta está desativada
			} else {                                 // Login correto e conta ativa
				cout << "Saldo atual: R$ " << saldo << endl; // Mostra o saldo da conta
			}                                        // Fim do if/else
			break;                                   // Sai do switch e volta ao menu

		case 4: // Opção 4: alterar tipo da conta
			cout << "\n4 - Alterar tipo da conta" << endl; // Exibe o título da opção
			if (contadorCliente == 0) {              // Verifica se ainda não há nenhuma conta
				cout << "Nenhuma conta cadastrada." << endl; // Informa que não há conta
				break;                               // Sai do switch e volta ao menu
			}                                        // Fim do if
			cout << "Insira o número da conta: ";    // Pede o número da conta
			cin >> numeroDigitado;                   // Lê o número digitado
			cout << "Insira a senha: ";              // Pede a senha
			cin >> senhaDigitada;                    // Lê a senha digitada

			if (numeroDigitado != numeroConta || senhaDigitada != senhaConta) { // Número da conta OU senha não conferem
				cout << "Número da conta ou senha incorretos." << endl;         // Avisa o erro de login
			} else if (!contaAtiva) {                // Login correto, mas a conta está desativada
				cout << "Conta desativada." << endl; // Avisa que a conta está desativada
			} else {                                 // Login correto e conta ativa
				do { // Repete até o novo tipo ser 1 ou 2
					cout << "Digite 1 para Corrente ou 2 para Poupança: "; // Pede o novo tipo
					cin >> tipoConta;                                      // Lê e já grava o novo tipo na conta
				} while (tipoConta != 1 && tipoConta != 2);                // Repete enquanto não for 1 nem 2
				cout << "Tipo da conta alterado para "                     // Início da mensagem de confirmação
				     << (tipoConta == 1 ? "Corrente" : "Poupança") << "." << endl; // Completa a mensagem com o novo tipo
			}                                        // Fim do if/else
			break;                                   // Sai do switch e volta ao menu

		case 5: // Opção 5: ativar/desativar conta
			cout << "\n5 - Ativar/Desativar conta" << endl; // Exibe o título da opção
			if (contadorCliente == 0) {              // Verifica se ainda não há nenhuma conta
				cout << "Nenhuma conta cadastrada." << endl; // Informa que não há conta
				break;                               // Sai do switch e volta ao menu
			}                                        // Fim do if
			cout << "Insira o número da conta: ";    // Pede o número da conta
			cin >> numeroDigitado;                   // Lê o número digitado
			cout << "Insira a senha: ";              // Pede a senha
			cin >> senhaDigitada;                    // Lê a senha digitada

			if (numeroDigitado != numeroConta || senhaDigitada != senhaConta) { // Número da conta OU senha não conferem
				cout << "Número da conta ou senha incorretos." << endl;         // Avisa o erro de login
			} else {                                 // Login correto (aqui a conta pode estar ativa ou não)
				do { // Repete até o usuário digitar 1 ou 0
					cout << "Digite 1 para ativar a conta e 0 para desativar: "; // Pede a escolha
					cin >> alterarConta;                                         // Lê a escolha digitada
				} while (alterarConta != 1 && alterarConta != 0);                // Repete enquanto não for 1 nem 0

				contaAtiva = (alterarConta == 1); // true se digitou 1 (ativar); false se digitou 0 (desativar)
				cout << "A conta foi " << (contaAtiva ? "ativada" : "desativada") // Escolhe a palavra conforme o novo estado
				     << " com sucesso." << endl;                                  // Completa a mensagem de confirmação
			}                                        // Fim do if/else
			break;                                   // Sai do switch e volta ao menu

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
