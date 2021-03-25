#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <TIME.H>

//variaveis globais
int volta_menu; //vari�vel global para retornar ao menu


//fun��o para abrir arquivo
FILE* AbreArquivo(char modo, char caminho[30]);
FILE* AbreArquivo(char modo, char caminho[30])
{
    FILE *arquivo;
    switch(modo)
    {
    case 'g':
        arquivo = fopen(caminho,"wt"); //abre o arquivo em modo de grava��o
        break;
    case 'l':
        arquivo = fopen(caminho,"rt"); //abre o arquivo em modo de leitura
        break;
    case 'a':
        arquivo = fopen(caminho,"a"); //abre o arquivo em um modo append
        break;
    }
    if(arquivo==NULL)  //Se houver algum erro, o ponteiro apontar� para NULL
    {
        printf("Nao foi poss�vel abrir o arquivo");
        exit(0);
    }
    return arquivo;
}

//void para fechar arquivo
void FecharArquivo(FILE *arquivo);
void FecharArquivo(FILE *arquivo)
{
    fclose(arquivo); //apenas usa a fun��o para fechar o arquivo com o ponteiro arquivo
}

// Fun��o para Cadastrar Feedbacks
void CadastraFeedback(char nome_medico[30], int nota_medico, int nota_atendimento);
void CadastraFeedback(char nome_medico[30], int nota_medico, int nota_atendimento)
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;

    arquivo = AbreArquivo('a', "Listafeedback.txt");//Abre o arquivo Lista de Feedbacks em modo append
    fprintf(arquivo, "%s %d %d \n", nome_medico, nota_medico, nota_atendimento);//Cadastra as vari�veis no arquivo texto
    FecharArquivo(arquivo);//fecha arquivo
}

//fun��o para Listar Feedbacks
void ListarFeedback();
void ListarFeedback()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Vari�veis e ponteiros
    FILE *arquivo;
    char nome_medico[30];
    int nota_medico;
    int nota_atendimento;

    arquivo = AbreArquivo('l',"ListaFeedback.txt");//Abre o arquivo Lista de Feedbacks em modo leitura
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %d %d",&nome_medico, &nota_medico, &nota_atendimento);//Escaneia todos as tudo que tem e adiciona nas vari�veis
        printf("| Nome Do M�dico:... %s         |\n| Nota do M�dico:............... %d |\n| Nota do atendimento:.......... %d |\n\n",nome_medico, nota_medico, nota_atendimento);//Printa na tela a Lista de Feedback
    }
    FecharArquivo(arquivo);//fecha arquivo

}

//fun��o para Deletar Feedbacks
void DeletarFeedback();
void DeletarFeedback()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;//Ponteiro

    remove("ListaFeedback.txt");//Deleta o arquivo Lista de Feedback
    remove("ListaFeedbackTemp.txt");//Deleta o arquivo Lista de Feedback Temp

    arquivo = AbreArquivo('g', "Listafeedback.txt");//Cria o arquivo Lista de Feedback novamente
    FecharArquivo(arquivo);//Fecha arquivo

    printf("\nFeedbacks Deletados\n\n");//Avisa que os feedbacks foram deletados
}

// fun��o para Agendar consultas
void Agendar(char nome[30], char ult_nome[30], char nome_medico[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], int dia_consulta, int hora_consulta, int minuto_consulta, char especialidade[30], char num_carteira[30], char unidade[20]);
void Agendar(char nome[30], char ult_nome[30], char nome_medico[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], int dia_consulta, int hora_consulta, int minuto_consulta, char especialidade[30], char num_carteira[30], char unidade[20])
{
    //ponteiro
    FILE *arquivo;

    arquivo = AbreArquivo('a', "ListaAgendamento.txt");//Abre o arquivo Lista Agendamento em modo append
    fprintf(arquivo, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//Escreve o foi pedido e estar nas vari�veis para o arquivo texto
    FecharArquivo(arquivo);//Fecha arquivo
}

// fun��o para Listar consultas
void ListarAgenda();
void ListarAgenda()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e Vari�veis
    FILE *arquivo;
    char nome[50];
    char ult_nome[50];
    char nome_medico[30];
    char numAnterior[50];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char unidade[20];

    arquivo = AbreArquivo('l',"ListaAgendamento.txt");//Abre arquivo Lista Agendamento em modo append
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);//Escaneia todos as tudo que tem e adiciona nas vari�veis
        if(strcmp(numAnterior,num_carteira) != 0)//Compara os n�meros de carteira para n�o dar um bug que aparecer a mesma consulta 2 vezes
        {
            strcpy(numAnterior,num_carteira);//Copia a vari�vel numAnterior no e cola em numCarteira para n�o ocorrer o bug que ira repetir 2 vezes a consulta
            printf("|------------------------------------------------------\n|Nome:...................... %s %s\n|Nome Do M�dico:............ %s\n|Telefone:.................. %s\n|CPF:....................... %s-%s\n|Dia da Consulta:........... %d\n|Hor�rio da Consulta:....... %d:%d\n|Especialidade:............. %s\n|Nc:........................ %s\n|Unidade:................... %s\n|------------------------------------------------------\n\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//printa todas as informa��es de agendamento
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
}

//fun��o para pesquisar consulta
void PesquisaAgendamento (char pesquisa_num[30]);
void PesquisaAgendamento (char pesquisa_num[30])
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //ponteiros e vari�veis
    FILE *arquivo;
    FILE *arquivoTemp;
    char nome[50];
    char ult_nome[50];
    char telefone[20];
    char nome_medico[30];
    char cpf_sdigito[15];
    char cpf_digito[15];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char numAnterior[50];
    char nomeAnterior[50];
    char unidade[20];
    bool achou = false;//Coloca essa vari�vel em FALSE para ter uma confirma��o de deletado mais a frente

    arquivo = AbreArquivo('l', "ListaAgendamento.txt");//Abre o arquivo Lista Agendamento em modo de leitura
    arquivoTemp = AbreArquivo('g', "PesquisaTemp.txt");//Abre o arquivo Lista Agendamento em modo de grava��o
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas vari�veis
        // Zero = s�o iguais
        // Diferente de Zero = n�o s�o iguais
        if(strcmp(nomeAnterior,nome) != 0)//Compara os nomes para n�o dar um bug que aparecer a mesma consulta 2 vezes
        {
            strcpy(nomeAnterior,nome);//Copia a vari�vel nomeAnterior no e cola em nome para n�o ocorrer o bug que ira repetir 2 vezes a consulta
            if(strcmp(pesquisa_num,num_carteira) == 0)//Compara o n�mero de carteira, se for igual printa no arquivo Temp a linha toda
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//printa a linha que seja igual os par�metros
            }
            else//Se n�o ele coloca a vari�vel "achou" em true
            {
                achou = true;
            }
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivo Temp


    arquivo = AbreArquivo('l',"PesquisaTemp.txt");//Abre arquivo Pesquisa Temp em modo leitura

    strcpy(nomeAnterior,"");//Copia nomeAnterior para "" para a vari�vel ficar vazia
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas vari�veis

        if(strcmp(nomeAnterior,nome) != 0 && strcmp(pesquisa_num,num_carteira) == 0)//Se nomeAnterior for diferente de nome e pesquisa_num por igual a num_carteira ele ir� printa as informa��es de pesquisa encontrados
        {
            strcpy(nomeAnterior,nome);
            printf("\n|------------------------------------------------------\n|Nome:...................... %s %s\n|Nome Do M�dico:............ %s\n|Telefone:.................. %s\n|CPF:....................... %s-%s\n|Dia da Consulta:........... %d\n|Hor�rio da Consulta:....... %d:%d\n|Especialidade:............. %s\n|Nc:........................ %s\n|Unidade:................... %s\n|------------------------------------------------------\n\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
            printf("Consulta(s) encontrado(s) com sucesso!\n\n");
        }
        if(strcmp(pesquisa_num,num_carteira) !=0)//se pesquisa_num for diferente de num_carteira ira printa Usuario n�o encontrado!
        {
            printf("Usuario n�o encontrado!\n\n");
        }
    }
}

// fun��o para Deletar consultas //pronta
void DeletarAgendamento(char nomeDeletarAgenda[50], char num_carteiraDeletar[30], int diaDeletar, int horarioDeletar, int minutoDeletar);
void DeletarAgendamento(char nomeDeletarAgenda[50], char num_carteiraDeletar[30], int diaDeletar, int horarioDeletar, int minutoDeletar)
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e Vari�veis
    FILE *arquivo;
    FILE *arquivoTemp;
    char nome[50];
    char ult_nome[50];
    char telefone[20];
    char nome_medico[30];
    char cpf_sdigito[15];
    char cpf_digito[15];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char numAnterior[50];
    char unidade[20];
    bool apagou = false;//Coloca essa vari�vel em FALSE para ter uma confirma��o de deletado mais a frente

    arquivo = AbreArquivo('l', "ListaAgendamento.txt");//Abre o arquivo Lista Agendamento em modo leitura
    arquivoTemp = AbreArquivo('g', "ListaAgendamentoTemp.txt");//Abre o arquivo Lista Agendamento em modo grava��o

    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas vari�veis
        // Zero = s�o iguais
        // Diferente de Zero = n�o s�o iguais
        if(strcmp(numAnterior,num_carteira) != 0)//Compara os nomes para n�o dar um bug que deleta 2 consultas
        {
            strcpy(numAnterior,num_carteira);//Copia a vari�vel numAnterior no e cola em num_carteira para n�o ocorrer o bug descrito acima
            if(strcmp(nomeDeletarAgenda,nome) != 0 && strcmp(num_carteiraDeletar,num_carteira) != 0 && diaDeletar != dia_consulta && horarioDeletar != hora_consulta && minutoDeletar != minuto_consulta)//compara os par�metros do If para confirmar se � a consulta certa antes de apagar
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//printa todas as consulta menos a que o usu�rio deseja apagar em Pesquisa Agendamento Temp
            }
            else
            {
                apagou = true;//se der algum erro apagou vira True
            }
        }
    }
    FecharArquivo(arquivo);//fecha arquivo
    FecharArquivo(arquivoTemp);//fecha arquivo Temp

    arquivo = AbreArquivo('g', "ListaAgendamento.txt");//Abre arquivo Lista Agendamento em modo grava��o
    arquivoTemp = AbreArquivo('l', "ListaAgendamentoTemp.txt");//Abre arquivo Lista Agendamento em modo de leitura

    strcpy(numAnterior,"");//Copia numAnterior para "NULL" para a vari�vel ficar vazia

    while(!feof(arquivoTemp))//Usa o loop para ler o arquivo todo com o ponteiro *arquivoTemp
    {
        fscanf(arquivoTemp,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas vari�veis
        if(strcmp(numAnterior,num_carteira))//Compara numAnterior com num_carteira
        {
            strcpy(numAnterior,num_carteira);//Copia a vari�vel numAnterior no e cola em num_carteira
            fprintf(arquivo, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//Printa todas as consultas menos a que foi deletada
        }
    }

    FecharArquivo(arquivo);//Fecha Arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivoTemp

    if(apagou)//Se apagou virou true ele ir� printar que o a consulta foi apagada com sucesso
    {
        printf("Agendamento de Consulta apagada com sucesso!\n\n");
    }
    else//Se apagou for falso ele ir� printar que o conveniado n�o foi encontrado
    {
        printf("Conveniado n�o encontrado!\n\n");

    }
}

//fun��o cadastra conveniado
void Cadastra(char nome[30], char ult_nome[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], char rg[15], int nascimento, char email[40], char num_carteira[30]);
void Cadastra(char nome[30], char ult_nome[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], char rg[15], int nascimento, char email[40], char num_carteira[30])
{
    //Ponteiros
    FILE *arquivo;

    arquivo = AbreArquivo('a', "ListaCadastro.txt");//Abre o arquivo Lista Cadastro em modo de append
    fprintf(arquivo, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);//Escreve o foi pedido e estar nas vari�veis para o arquivo texto
    FecharArquivo(arquivo);//Fecha arquivo
}

//fun��o para listar conveniados //pronta
void Listar();
void Listar()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e vari�veis
    FILE *arquivo;
    char nome[50];
    char ult_nome[50];
    char nomeAnterior[50];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    char rg[15];
    int nascimento;
    char email[40];
    char num_carteira[30];

    printf("LISTA DE CONVENIADOS");
    arquivo = AbreArquivo('l',"ListaCadastro.txt");//Abre o arquivo Lista Cadastro em modo de leitura
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que tem e adiciona nas vari�veis
        if(strcmp(nomeAnterior,nome) != 0)//Compara o nomeAnterior com o nome para n�o dar um bug que aparecer o mesmo conveniado 2 vezes
        {
            strcpy(nomeAnterior,nome);//Copia a vari�vel nomeAnteiror e cola em nome para n�o ocorrer o bug que ira repetir 2 vezes a consulta
            printf("\n|------------------------------------------------------\n|Nome:............. %s %s\n|Telefone:......... %s\n|CPF:.............. %s-%s\n|RG:............... %s\n|Nascimento:....... %d\n|Email:............ %s\n|Nc:............... %s\n|------------------------------------------------------\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
}

//fun��o para pesquisar conveniado
void PesquisaConveniado (char pesquisa_nome[50]);
void PesquisaConveniado (char pesquisa_nome[50])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e vari�veis
    FILE *arquivo;
    FILE *arquivoTemp;
    char nome[50];
    char ult_nome[50];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    char rg[15];
    int nascimento;
    char email[40];
    char num_carteira[30];
    char numAnterior[50];
    bool achou = false;

    arquivo = AbreArquivo('l', "ListaCadastro.txt");//Abre o arquivo Lista Cadastro em modo de leitura
    arquivoTemp = AbreArquivo('g', "PesquisaTemp.txt");//Abre o arquivo Lista Cadastro em modo de grava��o
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que tem e adiciona nas vari�veis
        // Zero = s�o iguais
        // Diferente de Zero = n�o s�o iguais
        if(strcmp(numAnterior,num_carteira) != 0)//Compara numAnterior com num_carteira para n�o ocorre o erro que repetirar 2 vezes o ultimo conveniado
        {
            strcpy(numAnterior,num_carteira);//Se o IF for diferente ele ira copiar o numAnterior e cola no num_carteira
            if(strcmp(pesquisa_nome,nome) == 0)//Compara o pesquisa_nome com o nome, se for igual ele irar printar em pesquisa Temp
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            }
            else
            {
                achou = true;
            }
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivoTemp


    arquivo = AbreArquivo('l',"PesquisaTemp.txt");//Abre o arquivo Pesquisa Temp em modo leitura

    strcpy(numAnterior,"");//Copia nomeAnterior para "NULL" para a vari�vel ficar vazia
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que tem e adiciona nas vari�veis
        if(strcmp(numAnterior,num_carteira) != 0 && strcmp(pesquisa_nome,nome) == 0)
        {
            strcpy(numAnterior,num_carteira);//Copia a vari�vel nomeAnterior no e cola em nome para n�o ocorrer o bug que copia 2 vezes
            printf("\n\n|------------------------------------------------------\n|Nome:............. %s %s\n|Telefone:......... %s\n|CPF:.............. %s-%s\n|RG:............... %s\n|Nascimento:....... %d\n|Email:............ %s\n|Nc:............... %s\n|------------------------------------------------------\n\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            printf("Usuario encontrado com sucesso!\n\n");
        }
        if(strcmp(pesquisa_nome,nome) !=0)//compara o pesquisa_nome e nome, se for diferente ele printa usu�rio n�o encontrado
        {
            printf("Usu�rio n�o encontrado!\n\n");
        }
    }
}

//fun��o para deletar conveniado
void Deletar(char num_Deletar[50]);
void Deletar(char num_Deletar[50])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e Vari�veis
    FILE *arquivo;
    FILE *arquivoTemp;
    char nome[50];
    char ult_nome[50];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    char rg[15];
    int nascimento;
    char email[40];
    char num_carteira[30];
    char nomeAnterior[50];
    bool apagou = false;//Coloca essa vari�vel em FALSE para ter uma confirma��o de deletado mais a frente

    arquivo = AbreArquivo('l', "ListaCadastro.txt");//Abre o arquivo Lista Cadastro em modo leitura
    arquivoTemp = AbreArquivo('g', "ListaCadastroTemp.txt");//Abre o arquivo Lista Cadastro Temp em modo grava��o

    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que estar em Lista Cadastro e joga nas vari�veis
        // Zero = s�o iguais
        // Diferente de Zero = n�o s�o iguais
        if(strcmp(nomeAnterior,nome) != 0)//Compara os nomes para n�o dar um bug que deleta 2 consultas
        {
            strcpy(nomeAnterior,nome);//Copia o nomeAnterior e cola em nome para n�o ocorrer o bug descrito acima
            if(strcmp(num_Deletar,num_carteira) != 0)//compara num_Deletar com num_carteira se for diferente ele copiar para lista cadastro temp
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            }
            else//Se n�o apagou vira true
            {
                apagou = true;
            }
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivo Temp
    arquivo = AbreArquivo('g', "ListaCadastro.txt");//Abre arquivo Lista Cadastro em modo de grava��o
    arquivoTemp = AbreArquivo('l', "ListaCadastroTemp.txt");//Abre arquivo Lista Cadastro em modo de leitura

    strcpy(nomeAnterior,"");//Copia nomeAnterior para "NULL" para a vari�vel ficar vazia

    while(!feof(arquivoTemp))//Usa o loop para ler o arquivo todo com o ponteiro *arquivoTemp
    {
        fscanf(arquivoTemp,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que estar em Lista Cadastro e joga nas vari�veis
        if(strcmp(nomeAnterior,nome) != 0)//Se nomeAnterior for diferente de nome ele copiar todos os arquivos de volta para Lista Cadastro
        {
            strcpy(nomeAnterior,nome);//Copia o nomeAnterior e cola em nome para n�o ocorrer o bug que ira apararecer o ultimo conveniado 2 vezes
            fprintf(arquivo, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
        }
    }

    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivo Temp

    if(apagou)//Se apagou for False ele ir� printar Conveniado deletado com sucesso
    {
        printf("Conveniado deletado com sucesso!\n\n");
    }
    else//Se apagou for true ele printa Conveniado n�o encontrado
    {
        printf("Conveniado n�o encontrado!\n\n");
    }
}


//fun��o para cadastrar Atendimento
void CadastraUserGeral(char login[30], char senha[30], char permissao[30]);
void CadastraUserGeral(char login[30], char senha[30], char permissao[30])
{
    //Ponteiro
    FILE *arquivo;

    arquivo = AbreArquivo('a', "SistemadeLoginGeral.txt");//Abre o arquivo Sistema de Login Geral em modo append
    fprintf(arquivo, "%s %s %s \n", login, senha, permissao); //printa as vari�veis no arquivo
    FecharArquivo(arquivo);//Fecha arquivo
}

//fun��o para deletar o usu�rio na sess�o de atendimento
void DeletarUserGeral(char deletarlogin[30]);
void DeletarUserGeral(char deletarlogin[30])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e Vari�veis
    FILE *arquivo;
    FILE *arquivoTemp;
    char login [30];
    char senha[30];
    char permissao[30];
    char verificalogin[30];
    char verificasenha[30];
    char loginAnterior[30];
    bool apagou = false;

    arquivo = AbreArquivo('l', "SistemadeLoginGeral.txt");//Abre o arquivo Sistema de Login Geral em modo de leitura
    arquivoTemp = AbreArquivo('g', "SistemadeLoginGeralTemp.txt");//Abre o arquivo Sistema de Login Geral em modo de grava��o

    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro arquivo
    {
        fscanf(arquivo,"%s %s %s", &login, &senha, &permissao);//Escaneia tudo que estar em Sistema de login Geral e joga nas vari�veis
        // Zero = s�o iguais
        // Diferente de Zero = n�o s�o iguais
        if(strcmp(loginAnterior,login) != 0)
        {
            strcpy(loginAnterior,login);
            if(strcmp(deletarlogin,login) != 0)//Compara os deletarlogin com login, se for diferente printa todos em Sistema de login Geral Temp
            {
                fprintf(arquivoTemp, "%s %s %s\n", login, senha, permissao);
            }
            else//Se n�o apagou vira True
            {
                apagou = true;
            }
        }
    }
    FecharArquivo(arquivo);//Fechar arquivo
    FecharArquivo(arquivoTemp);//Fechar arquivo Temp
    arquivo = AbreArquivo('g', "SistemadeLoginGeral.txt");//Abre o arquivo Sistema de Login Geral em modo de grava��o
    arquivoTemp = AbreArquivo('l', "SistemadeLoginGeralTemp.txt");//Abre o arquivo Sistema de Login Geral Temp em modo de leitura

    strcpy(loginAnterior,"");//Copia loginAnterior para "NULL" para a vari�vel ficar vazia

    while(!feof(arquivoTemp))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo Temp
    {
        fscanf(arquivoTemp,"%s %s %s", &login, &senha, &permissao);//Escaneia tudo que estar em Lista Cadastro e joga nas vari�veis
        if(strcmp(loginAnterior,login) != 0)//compara loginAnteriror com login se for diferente ele printa em Sistema de Login Geral Temp
        {
            strcpy(loginAnterior,login);//copiar loginAnterior e cola em login para n�o ocorrer o bug que apaga os 2 �ltimos logins da lista
            fprintf(arquivo, "%s %s %s\n", login, senha, permissao);
        }
    }

    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivo Temp

    if(apagou)//Se apagou for False ele ir� printar usu�rio deletado com sucesso
    {
        printf("Usu�rio deletado com sucesso!\n\n");
    }
    else//Se apagou for True printar usu�rio n�o encontrado
    {
        printf("Usuario n�o encontrado!\n\n");

    }
}

//Fun��o que lista todos os usu�rios no sistema
void ListarUserGeral();
void ListarUserGeral()
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiro e Vari�veis
    FILE *arquivo;
    char login[30];
    char senha[30];
    char permissao[30];
    char nomeAnterior[50];

    printf("LISTA DE USUARIOS\n");

    arquivo = AbreArquivo('l',"SistemadeLoginGeral.txt");//Abre o arquivo Sistema de Login Geral em modo de leitura
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro arquivo
    {
        fscanf(arquivo,"%s %s %s", &login, &senha, &permissao);//Escaneia tudo que estar em Sistema de login Geral e joga nas vari�veis
        if(strcmp(nomeAnterior,login) != 0)//Compara o nomeAnterior com login para n�o acontecer um bug que mostra o ultimo login, senha e permiss�o 2 vezes
        {
            strcpy(nomeAnterior,login);//copia nomeAnterior com login para n�o ocorrer o bug descrito acima
            printf("\n|------------------------------------------------------\n|Nome:............. %s \n|Senha:............. %s \n|Permiss�o:............. %s", login, senha, permissao);//printa na tela os logins com senha e permiss�o
        }
    }
    FecharArquivo(arquivo);//Fechar arquivo
}

//fun��o para cadastrar consulta no faturamento
void CadastraRelatorioFaturamento(char nome[30], char ult_nome[30], char num_carteira[30], int gasto_consulta, int dia_consulta, int mes_consulta, int ano_consulta);
void CadastraRelatorioFaturamento(char nome[30], char ult_nome[30], char num_carteira[30], int gasto_consulta, int dia_consulta, int mes_consulta, int ano_consulta)
{

    //Ponteiro
    FILE *arquivo;

    arquivo = AbreArquivo('a', "Relatorio.txt");//Abre o arquivo Relatorio em modo append
    fprintf(arquivo, "%s %s %s %d %d %d %d\n", nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta); //printa as vari�veis no arquivo
    FecharArquivo(arquivo);//fecha arquivo

}

//fun��o para listar o faturamento
void ListarRelatorioFaturamento();
void ListarRelatorioFaturamento()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e vari�veis
    FILE *arquivo;
    char nome[50];
    char ult_nome[50];
    char numAnterior[30];
    char num_carteira[30];
    int gasto_consulta;
    int dia_consulta;
    int mes_consulta;
    int ano_consulta;

    printf("\nFaturamento Mensal: \n");

    arquivo = AbreArquivo('l',"Relatorio.txt");//Abre o arquivo Relat�rio em modo de leitura
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro arquivo
    {
        fscanf(arquivo,"%s %s %s %d %d %d %d", &nome, &ult_nome, &num_carteira, &gasto_consulta, &dia_consulta, &mes_consulta, &ano_consulta);//Escaneia tudo que estar em Relatorio e joga nas vari�veis
        printf("|Nome: \t\tNC: \t   Gastos do paciente:   data: \n|%s %s  |  %s |  %d                | %d/%d/%d \n\n", nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta);//printa nas telas as vari�veis
    }
    FecharArquivo(arquivo);//fecha arquivo
}

//Pede pra o usuario escolher voltar pro menu ou fazer outra a��o
int volta_menu_login();
int volta_menu_login()
{

    do
    {
        printf("Digite 0 para sair para o menu: ");//pergunta para o usu�rio se deseja retornar ao menu de login
        scanf("%d", &volta_menu);

        if(volta_menu == 0)//Se o usu�rio digitar 0 ele retorna ao menu de login
        {
            system("cls");
            return main();
        }
        else//Se ele digitar outra coisa printa na tela op��o inv�lida e faz um loop para voltar ao come�o da fun��o
        {
            system("cls");
            printf("\nOp��o Inv�lida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 0);
}

//Pede pra o usu�rio escolher voltar pro menu ou fazer outra a��o
int volta_menu_atendimento();
int volta_menu_atendimento()
{

    do
    {
        printf("Digite 1 para retornar ao menu: ");//pergunta para o usu�rio se deseja retornar ao menu de atendimento
        scanf("%d", &volta_menu);

        if(volta_menu == 1)//Se o usu�rio digitar 0 ele retorna ao menu de atendimento
        {
            return principal_atendente();
        }
        else
        {
            printf("\nOp��o Invalida\n\n");//Se ele digitar outra coisa printa na tela op��o inv�lida e faz um loop para voltar ao come�o da fun��o
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

//Pede para o usuario escolher voltar para o menu ou fazer outra a��o
int volta_menu_medico();
int volta_menu_medico()
{

    do
    {
        printf("Digite 1 para retornar ao menu: ");//pergunta para o usu�rio se deseja retornar ao menu de m�dico
        scanf("%d", &volta_menu);

        if(volta_menu == 1)
        {
            return principal_medico();//Se o usu�rio digitar 0 ele retorna ao menu de m�dico
        }
        else//Se ele digitar outra coisa printa na tela op��o inv�lida e faz um loop para voltar ao come�o da fun��o
        {
            printf("\nOp��o Invalida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

//Pede para o usu�rio escolher voltar pro menu ou fazer outra a��o
int volta_menu_conveniado();
int volta_menu_conveniado()
{

    do
    {
        printf("Digite 1 para retornar ao menu: ");//pergunta para o usu�rio se deseja retornar ao menu de m�dico
        scanf("%d", &volta_menu);

        if(volta_menu == 1){//Se o usu�rio digitar 0 ele retorna ao menu de conveniado


            return principal_conveniado();
        }else//Se ele digitar outra coisa printa na tela op��o inv�lida e faz um loop para voltar ao come�o da fun��o
        {
            printf("\nOp��o Invalida\n\n");
            sleep(0,5);
        }
    }while(volta_menu != 1);
}

//Pede pra o usu�rio escolher voltar pro menu ou fazer outra a��o
int volta_menu_adm();
int volta_menu_adm()
{

    do
    {
        printf("\nDigite 1 para retornar ao menu: ");//pergunta para o usu�rio se deseja retornar ao menu de administrador
        scanf("%d", &volta_menu);

        if(volta_menu == 1)//Se o usu�rio digitar 0 ele retorna ao menu de conveniado
        {
            return principal_adm();
        }
        else//Se ele digitar outra coisa printa na tela op��o inv�lida e faz um loop para voltar ao come�o da fun��o
        {
            printf("\nOp��o Invalida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

//fun��o para logar Atendimento //pronta
void sistemadeloginGeral();
void sistemadeloginGeral()
{
    //Ponteiros e Vari�veis
    FILE *arquivo;
    char login [30];
    char senha[30];
    char permissao[30];
    char verificalogin[30];
    char verificasenha[30];
    bool achou = false;//Coloca essa vari�vel em FALSE para ter uma confirma��o mais a frente

    do
    {
        printf("Digite seu login: ");//Aqui ele ir� pedi o login e senha e adicionar nas vari�veis
        setbuf(stdin,NULL);
        gets(verificalogin);
        printf("\nDigite sua senha: ");
        setbuf(stdin,NULL);
        gets(verificasenha);


        arquivo = AbreArquivo('l',"SistemadeLoginGeral.txt");//Abre o arquivo Sistema de login Geral em modo leitura
        while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro arquivo
        {
            fscanf(arquivo, "%s %s %s", &login, &senha, &permissao);//Escaneia todos os logins, senhas e permiss�es
            if(strcmp(verificalogin, login) == 0 && strcmp(verificasenha, senha) == 0)//compara o login, senha e permiss�es do arquivo com as digitadas pelo o usu�rio
            {
                achou = true;//se o login e senha forem iguais achou vira True
                if(strcmp(permissao, "Medico") == 0 )//Se a permiss�o que o usu�rio for igual a medico ele entrar� no menu de m�dico
                {
                    printf("Bem vindo Doutor (a).");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(1,5);
                    system("cls");
                    principal_medico();
                }

                if(strcmp(permissao, "Atendente") == 0 )//Se a permiss�o que o usu�rio for igual a atendente ele entrar� no menu de atendimento
                {
                    principal_atendente();
                    printf("Bem vindo Atendente");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(1,5);
                    system("cls");
                }

                if(strcmp(permissao, "Administrador") == 0 )//Se a permiss�o que o usu�rio for igual a Administrador ele entrar� no menu de administrador
                {
                    printf("Bem vindo Administrador");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(1,5);
                    system("cls");
                    principal_adm();
                }

            }
            else//Se o login e a senha for diferente achou ira ser False e ele ir� printa a mensagem na tela
            {
                printf("Caso Esqueceu seu login ou senha entre em contato com o administrador\nd4niel.arruda@gmail.com\n\nESPERE\n");
                sleep(2);
                system("cls");
            }
        }

    }
    while(!achou);//Depois ir� dar o loop para repetir a fun��o
    FecharArquivo(arquivo);//Fecha arquivo

}

//tela de menu do atendimento e suas fun��es
void principal_atendente();
void principal_atendente()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Vari�veis
    int escolha_tela_atendente;
    char nome[30];
    char nome_medico[30];
    char ult_nome[30];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    char rg[15];
    int nascimento;
    char email[40];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char unidade[20];

    //Menu do Atendimento
    system("cls");
    printf("\n\t\tMENU");
    printf("\n");
    printf("\t ------------------------------------------");
    printf("\n\t| 1 - Cadastrar conveniado                 |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 2 - Listar conveniados                   |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 3 - Pesquisar conveniados                |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 4 - Deletar cadastro                     |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 5 - Agendar Consulta                     |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 6 - Listar Consultas                     |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 7 - Pesquisar Consultas                  |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 8 - Deletar Consultas                    |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 9 - Situa��o dos feedbacks               |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 10 - Deletar feedbacks                   |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 11 - Relat�rios de faturamento  e tabela |\n");
    printf("\t ------------------------------------------");
    printf("\n\t| 0 - Sair                                 |\n");
    printf("\t ------------------------------------------");


    printf("\nDigite uma opcao: ");//Pede para escolher um op��o
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_atendente);

    sleep(1);
    system("cls");//limpa a tela

    switch (escolha_tela_atendente)
    {
    case 1:
        //Cadastrar conveniado

        //Pede as informa��es para ser adicionada em Cadastra
        printf("\nDigite o nome: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(nome);
        printf("\nDigite o ultimo nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite o telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite os 9 primeiros n�mero do seu CPF sem ponto ou tra�o: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os �ltimos 2 n�meros do seu CPF: ");
        setbuf(stdin,NULL);
        gets(cpf_digito);
        printf("\nDigite o RG: ");
        setbuf(stdin,NULL);
        gets(rg);
        printf("\nDigite o Nascimento: ");
        scanf("%d", &nascimento);
        printf("\nDigite o Email: ");
        setbuf(stdin,NULL);
        gets(email);
        printf("\nDigite o n�mero da carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteira);
        Cadastra(nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);//Depois que coloca o que foi pedido nas veri�veis ele come�a a fun��o cadastra
        volta_menu_atendimento();//Depois que ele terminar a fun��o cadastra ele pode escolher se vai voltar para o menu
        break;

    case 2:
        //Listar conveniados
        Listar();//Fun��o para listar
        volta_menu_atendimento();
        break;

    case 3:
        //pesquisar conveniado
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char pesquisa_nome[50];

        printf("\nDigite o nome do conveniado que deseja procurar: ");
        setbuf(stdin,NULL);
        gets(pesquisa_nome);
        PesquisaConveniado(pesquisa_nome);
        volta_menu_atendimento();
        break;

    case 4:
        //Deletar cadastro
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char num_Deletar[50];

        printf("\nDigite o n�mero de carteira do conveniado que deseja deletar: ");
        setbuf(stdin,NULL);
        gets(num_Deletar);
        Deletar(num_Deletar);
        volta_menu_atendimento();
        break;

    case 5:
        //cadastrar agenadamento
        //Pede as informa��es para ser adicionada em Agendar
        printf("\nDigite o nome: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(nome);
        printf("\nDigite o ultimo nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite o telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite o nome do m�dico: ");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite os 9 primeiros n�mero do seu CPF sem ponto ou tra�o: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os �ltimos 2 n�meros do seu CPF: ");
        setbuf(stdin,NULL);
        gets(cpf_digito);
        printf("\nDigite o dia, m�s e ano da consulta sem barra: ");
        scanf("%d", &dia_consulta);
        printf("\nDigite a hora da consulta: ");
        scanf("%d", &hora_consulta);
        printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", hora_consulta);
        scanf("%d", &minuto_consulta);
        printf("\nDigite a especialidade da consulta: ");
        setbuf(stdin,NULL);
        gets(especialidade);
        printf("\nDigite o n�mero da carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteira);
        printf("\n| Paz | Cancioneiro | Paulista |");
        printf("\nDigite a o nome da unidade: ");
        setbuf(stdin,NULL);
        gets(unidade);
        Agendar(nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
        volta_menu_atendimento();
        break;

    case 6:
        //listar agendamentos
        ListarAgenda();
        volta_menu_atendimento();
        break;

    case 7:
        //pesquisa agendamento
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char pesquisa_num[30];

        printf("\nDigite o n�mero de carteirinha do paciente para v� as consultas do conveniado: ");
        setbuf(stdin,NULL);
        gets(pesquisa_num);
        PesquisaAgendamento(pesquisa_num);
        volta_menu_atendimento();
    case 8:
        //deletar agendamentos
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char nomeDeletar[50];
        char nomeDeletarAgenda[50];
        char num_carteiraDeletar[30];
        int diaDeletar;
        int horarioDeletar;
        int minutoDeletar;

        printf("\nDigite um nome: ");
        setbuf(stdin,NULL);
        gets(nomeDeletar);
        printf("\nDigite o n�mero de carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteiraDeletar);
        printf("\nDigite o dia, m�s e ano da consulta sem barra: ");
        scanf("%d", &diaDeletar);
        printf("\nDigite a hora da sua consulta: ");
        scanf("%d", &horarioDeletar);
        printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", hora_consulta);
        scanf("%d", &minutoDeletar);
        DeletarAgendamento(nomeDeletarAgenda, num_carteiraDeletar, diaDeletar, horarioDeletar, minutoDeletar);
        volta_menu_atendimento();
        break;

    case 9:
        //listar feedbacks
        ListarFeedback();
        volta_menu_atendimento();
        break;

    case 10:
        //excluir feedbacks
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        int excluir_feedback;

        printf("Para n�o haver manipula��o dos feedbacks a fun��o deletar feedback excluir todos os feedbacks de uma vez.\n\n");
        printf("Se tive certeza disso digite 1 se n�o digite 0 para voltar ao menu: ");
        scanf("%d", &excluir_feedback);


        if(excluir_feedback == 1)//If para ter a certeza de exclus�o dos feedbacks
        {
            DeletarFeedback();
        }
        else
        {
            volta_menu_atendimento();
        }
        break;

    case 11:
        ;
        //menu com relat�rios
        int escolha_menu_relatorio;
        //Menu de relat�rios e tabela
        printf("\n\t\Relat�rios de faturamento");
        printf("\n");
        printf("\t ---------------------------------------------");
        printf("\n\t| 1 - Adicionar faturamento no relat�rio    |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 2 - Listar Faturamento                    |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 3 - Tabela de Pre�o de Consultas e Exames |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 0 - Sair                                  |\n");
        printf("\t|---------------------------------------------");

        printf("\nDigite uma op��o: ");
        sleep(0,5);
        sleep(0,5);//pausa a tela por x segundos
        scanf("%d", &escolha_menu_relatorio);

        sleep(1);
        system("cls");//limpa a tela

        switch (escolha_menu_relatorio)
        {
        case 1:
            //Cadastrar relat�rio
            ;//Para pode colocar um char dentro de um case precisar adicionar este ";"

            char nome[30];
            char ult_nome[30];
            char num_carteira[30];
            int gasto_consulta;
            int dia_consulta;
            int mes_consulta;
            int ano_consulta;

            printf("\nDigite o nome do conveniado: ");
            setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
            gets(nome);
            printf("\nDigite o �ltimo nome do conveniado: ");
            setbuf(stdin,NULL);
            gets(ult_nome);
            printf("\nDigite o n�mero da carteirinha: ");
            setbuf(stdin,NULL);
            gets(num_carteira);
            printf("\nDigite o gasto da consulta hoje: ");
            scanf("%d", &gasto_consulta);
            printf("\nDigite o dia da consulta: ");
            scanf("%d", &dia_consulta);
            printf("\nDigite o m�s da consulta: ");
            scanf("%d", &mes_consulta);
            printf("\nDigite o ano da consulta: ");
            scanf("%d", &ano_consulta);
            CadastraRelatorioFaturamento(nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta);
            volta_menu_atendimento();
            break;

        case 2:
            //Listar Relat�rio
            ListarRelatorioFaturamento();//Lista Relat�rio
            volta_menu_atendimento();
            break;

        case 3:
            printf("TABELA DE CONSULTAS E EXAMES\n\n");
            printf("|------------------------------------------------------------------\n");
            printf("|Consulta Com Clinico Geral:......................... R$ 50,00\n\n");
            printf("|Consulta Com Especialistas:......................... R$ 90,00\n\n");
            printf("|Hemograma Completo:................................. R$ 75,00\n\n");
            printf("|Raio X:............................................. R$ 40,00\n\n");
            printf("|Raio X Panor�mico:.................................. R$ 40,00\n\n");
            printf("|Resson�ncia Magn�tica Mama:......................... R$ 300,00\n\n");
            printf("|Resson�ncia Magn�tica Pr�stata:..................... R$ 320,00\n\n");
            printf("|Ultrasson Mamas:.................................... R$ 55,00\n\n");
            printf("|Ultrasson Pr�stata Abdominal:....................... R$ 55,00\n\n");
            printf("|Ultrasson Pr�stata Transretal:...................... R$ 65,00\n\n");
            printf("|Urografia Venosa Excretora:......................... R$ 160,00\n\n");
            printf("|Urografia Venosa Minutada:.......................... R$ 220,00\n");
            printf("|-------------------------------------------------------------------\n");

            volta_menu_atendimento();
            break;
        case 0:
            //volta ao menu de Atendimento
            volta_menu_atendimento();
            break;

        default:
            printf("Op��o incorreta\n");
            sleep(1,25);
            volta_menu_atendimento();
            break;
        }
        break;

    case 0:
        //volta ao menu de login
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\n\Op��o invalida! Tente Novamente!\n\n");
        sleep(1,5);
        volta_menu_atendimento();
        break;
    }



}

//tela de menu do conveniado e suas fun��es
void principal_conveniado();
void principal_conveniado()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Vari�veis
    int escolha_tela_conveniado;
    char nome[30];
    char nome_medico[30];
    char ult_nome[30];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char unidade[20];

    //Menu de conveniado
    system("cls");
    printf("\n\t\tMENU");
    printf("\n");

    printf("\t|-----------------------------");
    printf("\n\t| 1 -  Agendar Consulta       |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 2 - Listar Suas Consultas   |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 3 - Desmarcar Suas consultas|\n");
    printf("\t|-----------------------------");
    printf("\n\t| 4 - Dar um feedback         |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 5 - Nossos Endere�os        |\n");
    printf("\t| -----------------------------");
    printf("\n\t| 0 - Sair                    |\n");
    printf("\t|-----------------------------");

    printf("\nDigite uma op��o: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_conveniado);

    sleep(1);
    system("cls");//limpa a tela
    //Switch para escolha de op��es no menu
    switch(escolha_tela_conveniado)
    {
    case 1:
        //cadastrar agendamento
        //Pede as informa��es para ser adicionada em Agendar
        printf("\nDigite seu primeiro nome: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(nome);
        printf("\nDigite seu �ltimo nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite seu telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite o nome do m�dico: ");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite os 9 primeiros n�mero do seu CPF sem ponto ou tra�o: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os �ltimos 2 n�meros do seu CPF: ");
        setbuf(stdin,NULL);
        gets(cpf_digito);
        printf("\nDigite o dia, m�s e ano que voc� deseja marcar a consulta sem barra: ");
        scanf("%d", &dia_consulta);
        printf("\nDigite o horario que voc� deseja para a sua consulta: ");
        scanf("%d", &hora_consulta);
        printf("\nHorario: %d:00 \nDigite o minuto que voc� deseja para a sua consulta: ", hora_consulta);
        scanf("%d", &minuto_consulta);
        printf("\nDigite a especialidade da consulta: ");
        setbuf(stdin,NULL);
        gets(especialidade);
        printf("\nDigite o n�mero da carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteira);
        printf("\n| Paz | Cancioneiro | Paulista |");
        printf("\nDigite a o nome da unidade: ");
        setbuf(stdin,NULL);
        gets(unidade);
        Agendar(nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
        volta_menu_conveniado();
        break;

    case 2:
        //pesquisa agendamento
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char pesquisa_num[30];

        printf("\nDigite o n�mero de carteirinha para ver suas consultas: ");
        setbuf(stdin,NULL);
        gets(pesquisa_num);
        PesquisaAgendamento(pesquisa_num);
        volta_menu_conveniado();
        break;

    case 3:
        //deletar agendamentos
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char nomeDeletar[50];
        char nomeDeletarAgenda[50];
        char num_carteiraDeletar[30];
        int diaDeletar;
        int horarioDeletar;
        int minutoDeletar;

        printf("\nDigite um nome: ");
        setbuf(stdin,NULL);
        gets(nomeDeletar);
        printf("\nDigite o n�mero de carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteiraDeletar);
        printf("\nDigite o dia, m�s e ano da consulta sem barra: ");
        scanf("%d", &diaDeletar);
        printf("\nDigite o hora da sua consulta: ");
        scanf("%d", &horarioDeletar);
        printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", horarioDeletar);
        scanf("%d", &minutoDeletar);
        DeletarAgendamento(nomeDeletarAgenda, num_carteiraDeletar, diaDeletar, horarioDeletar, minutoDeletar);
        volta_menu_conveniado();
        break;

    case 4:
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char nome_medico[30];
        int nota_medico;
        int nota_atendimento;

        printf("\nDigite o nome do m�dico");
        printf("(Andre) (Osvaldo) (Luis): ");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite uma nota de 0 a 10 para o atendimento de seu m�dico: ");
        scanf("%d", &nota_medico);
        printf("\nDigite uma nota de 0 a 10 para seu atendimento em geral: ");
        scanf("%d", &nota_atendimento);
        printf("Muito Obrigado pelo seu Feedback :)\n\n");
        CadastraFeedback(nome_medico, nota_medico, nota_atendimento);
        volta_menu_conveniado();

        break;

    case 5:
        //Aqui mostra o endere�o das cl�nicas e o contato das mesmas
        printf("Onde voc� pode nos encontrar :)\n");

        printf("\n|----------------------------------------------------------------------------------------------|\n");
        printf("|   CLINICA PRINCIPAL: R. da Paz, 797 - Ch�cara Santo Ant�nio, S�o Paulo - SP, 04713-000\n");
        printf("|   Tel.: (11) 5181-4055 \n");
        printf("|----------------------------------------------------------------------------------------------|\n");

        printf("|   2� CLINICA: Rua Cancioneiro Popular, 210 - Ch�cara Santo Ant�nio S�o Paulo - SP, 04710-000\n");
        printf("|   Tel.: (11) 2114-4000 \n");
        printf("|----------------------------------------------------------------------------------------------|\n");

        printf("|   Av. Paulista, 900 - Cerqueira C�sar S�o Paulo - SP CEP 01310-100\n");
        printf("|   Tel.: (11) 3170-3700 \n");
        printf("|----------------------------------------------------------------------------------------------|\n\n");

        volta_menu_conveniado();
        break;

    case 0:
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\n\Op��o invalida! Tente Novamente! \n\n");
        sleep(1,5);
        volta_menu_conveniado();
        break;
    }
}

//tela de menu do administrador e suas fun��es
void principal_adm();
void principal_adm()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    char login[30];
    char senha[30];
    char permissao[30];
    int escolha_tela_adm;

    //Menu de Administrador do sistema
    system("cls");
    printf("\n\t\tMENU");
    printf("\n");

    printf("\t|-----------------------------");
    printf("\n\t| 1 - Adicionar Usu�rios      |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 2 - Listar Usu�rios         |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 3 - Deletar Usu�rios        |\n");
    printf("\t -----------------------------");
    printf("\n\t| 0 - Sair                    |\n");
    printf("\t -----------------------------");


    printf("\n\nDigite uma op��o: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_adm);

    sleep(1);
    system("cls");//limpa a tela
    //Switch de escolha de op��es no menu de Administrador
    switch (escolha_tela_adm)
    {
    case 1:
        //Pede as informa��es para ser adicionada como um novo usu�rio
        printf("Digite o nome do novo usu�rio: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(login);
        printf("\nDigite a Senha do novo usu�rio: ");
        setbuf(stdin,NULL);
        gets(senha);
        printf("\nDigite o tipo de Permiss�o que desejar dar ao usu�rio");
        printf("\n(Administador) (Medico) (Atendimento) (Conveniado)");
        printf(": ");
        setbuf(stdin,NULL);
        gets(permissao);
        CadastraUserGeral(login, senha, permissao);
        volta_menu_adm();
        break;

    case 2:
        //Lista todos os usu�rios
        ListarUserGeral();
        volta_menu_adm();
        break;

    case 3:
        //Deleta usu�rios
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char deletarlogin[30];
        printf("\nDigite o nome do usu�rio que deseja deletar: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(deletarlogin);
        DeletarUserGeral(deletarlogin);
        volta_menu_adm();
        break;

    case 0:
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\n\nOp��o invalida! Tente Novamente! \n\n");
        sleep(1,5);
        volta_menu_adm();
        break;
    }
}

//tela de menu do m�dico e suas fun��es
void principal_medico();
void principal_medico()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    int escolha_tela_medico;

    system("cls");
    printf("\n\t\tMENU");
    printf("\n");
    //Menu de M�dico
    printf("\t|--------------------------------------");
    printf("\n\t| 1 - Pesquisar Agendamento            |\n");
    printf("\t|--------------------------------------");
    printf("\n\t| 2 - Listar conveniados               |\n");
    printf("\t| -------------------------------------");
    printf("\n\t| 3 - Pesquisar conveniado             |\n");
    printf("\t|--------------------------------------");
    printf("\n\t| 0 - Sair                             |\n");
    printf("\t| -------------------------------------\n");

    printf("\nDigite uma op��o: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_medico);

    sleep(1);
    system("cls");//limpa a tela
    //Switch para escolha de op��es no menu M�dico
    switch (escolha_tela_medico)
    {
    case 1:
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char pesquisa_num[30];

        printf("\nDigite o n�mero de carteirinha do paciente para ver suas consultas: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(pesquisa_num);
        PesquisaAgendamento(pesquisa_num);
        volta_menu_medico();
        break;

    case 2:
        //Listar conveniados
        Listar();
        volta_menu_medico();
        break;

    case 3:
        //pesquisar conveniado
        ;
        char pesquisa_nome[50];

        printf("\nDigite o nome do conveniado que deseja procurar: ");
        setbuf(stdin,NULL);
        gets(pesquisa_nome);
        PesquisaConveniado(pesquisa_nome);
        volta_menu_medico();
        break;

    case 0:
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\nOp��o incorreta\n");
        sleep (1,2);
        principal_medico();
        break;
    }




}


int main ()
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR

    int login_escolha; // vari�vel usada no int main para escolher usu�rio
    int login_menu;
    //No int main deixamos apenas a tela de login para uma melhor organiza��o do c�digo em si
    printf("\n");
    printf("\t\t\t\t\t\t*!Bem vindo!*\n\n");
    printf("\tDATA : %s\n\n\n",__DATE__);//Para aparecer a data perto do bem vindo
    sleep(1);

    printf("\n\t\t\t\t\t\t  | Usu�rios | \t\t");
    printf("\n\t\t__________________________________________________________________________________\n\n");
    printf("\t\t|       0-Sair \t\t\t  1-Conveniado \t\t\t2-Usu�rios       |\n");
    printf("\t\t__________________________________________________________________________________\n\n");

    printf("\n\tEscolha um op��o por favor --> ");

    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &login_escolha);
    sleep(1);
    system("cls");//limpa a tela

    //Switch para escolha de login
    switch(login_escolha)
    {
    case 0:
        return 0;
        break;

    case 1:
        printf("Bem vindo Conveniado");
        sleep(2);
        system("cls");
        printf("Carregando...");
        sleep(2);
        system("cls");
        principal_conveniado();

    case 2:
        sistemadeloginGeral();
        break;
    default:
        printf("op��o incorreta");
        sleep(1,25);
        system("cls");
    }
    return 0;
}
