#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

typedef struct{

    char nomeArma[40];
    int ataque;

} arma;

typedef struct{

    char nome[40];
    int ataque;
    int mana;

} habilidade;

typedef struct{

    char nomeClasse[10];
    arma armaEspecifica;
    habilidade habilidadeEspecial;

} classe; //Atributos da classe do jogador

typedef struct{

    int level;
    int pts;
    int ptsNec;

} level;

typedef struct{

    classe limitacoes;
    level level;
    char nomePersonagem[50];
    int vida;
    int ataque;
    int defesa;
    int mana;

} personagem; //Atributos referentes ao personagem do jogador.

typedef struct{

    personagem personagem;
    int progresso;
    char login[20];
    char senha[20];

} usuario; //Atributos referentes ao jogador.

typedef struct{

    usuario saveDoUsuario;

}save; //Atributos do save.

typedef struct{

    char nomeMonstro[50];
    int vida;
    int ataque;
    int defesa;

} monstro;

int checaClasse(int *classeEscolhida, usuario *userMain){

    char arqueiro[] = "arqueiro";
    char guerreiro[] = "guerreiro";
    char mago[] = "mago";

    //strlwr é necessário para padronização, dessa forma, nosso programa não é case sensitive
    //strncmp vai apenas comparar duas strings com a delimitação marcada no último argumento
    if(strncmp( strlwr(userMain->personagem.limitacoes.nomeClasse) , arqueiro, 7)==0){

        //habilidade específica da classe, o seu nome não muda mas o seu dano será alterado conforme o nível
        strcpy(userMain->personagem.limitacoes.habilidadeEspecial.nome, "Chuva de Flechas");
        userMain->personagem.limitacoes.habilidadeEspecial.ataque = 30;
        userMain->personagem.limitacoes.habilidadeEspecial.mana = 25;

        //status da arma inicial recebida ao escolher uma classe, esses status serão mudados com o tempo
        strcpy(userMain->personagem.limitacoes.armaEspecifica.nomeArma, "Arco Inicial");
        userMain->personagem.limitacoes.armaEspecifica.ataque = 20;

        //status base do personagem que opta por ser um arqueiro
        userMain->personagem.ataque = 20;
        userMain->personagem.defesa = 20;
        userMain->personagem.vida = 240;
        userMain->personagem.mana = 90;

        printf("\nVocê se tornou um arqueiro. Arqueiros não são especializados em nenhum tipo de status,");
        printf("\ntambém não lhes falta nada, é o meio termo se comparado às outras classes");
        printf("\nFoi aquirido: Habilidade Especial - %s", userMain->personagem.limitacoes.habilidadeEspecial.nome);
        printf("\n");

        return 1;

    }else{

        if(strncmp( strlwr(userMain->personagem.limitacoes.nomeClasse) , guerreiro, 9)==0){

            //habilidade específica da classe, o seu nome não muda mas o seu dano será alterado conforme o nível
            strcpy(userMain->personagem.limitacoes.habilidadeEspecial.nome, "Espadada Profunda");
            userMain->personagem.limitacoes.habilidadeEspecial.ataque = 20;
            userMain->personagem.limitacoes.habilidadeEspecial.mana = 30;

            //status da arma inicial recebida ao escolher uma classe, esses status serão mudados com o tempo
            strcpy(userMain->personagem.limitacoes.armaEspecifica.nomeArma, "Espada Inicial");
            userMain->personagem.limitacoes.armaEspecifica.ataque = 30;

            //status base do personagem que opta por ser um guerreiro
            userMain->personagem.ataque = 30;
            userMain->personagem.defesa = 25;
            userMain->personagem.vida = 300;
            userMain->personagem.mana = 80;

            printf("\nVocê se tornou um guerreiro. Os guerreiros tem uma defesa um pouco maior porém tem mana e ataque especial reduzidos");
            printf("\nFoi aquirido: Habilidade Especial - %s", userMain->personagem.limitacoes.habilidadeEspecial.nome);
            printf("\n");

            return 2;

        }else{

            if(strncmp( strlwr(userMain->personagem.limitacoes.nomeClasse) , mago, 4)==0){

            //habilidade específica da classe, o seu nome não muda mas o seu dano será alterado conforme o nível
            strcpy(userMain->personagem.limitacoes.habilidadeEspecial.nome, "Bola de Fogo");
            userMain->personagem.limitacoes.habilidadeEspecial.ataque = 60;
            userMain->personagem.limitacoes.habilidadeEspecial.mana = 20;

            //status da arma inicial recebida ao escolher uma classe, esses status serão mudados com o tempo
            strcpy(userMain->personagem.limitacoes.armaEspecifica.nomeArma, "Cajado Inicial");
            userMain->personagem.limitacoes.armaEspecifica.ataque = 20;

            //status base do personagem que opta por ser um mago
            userMain->personagem.ataque = 10;
            userMain->personagem.defesa = 15;
            userMain->personagem.vida = 200;
            userMain->personagem.mana = 100;

            printf("\nVocê se tornou um mago, a linhagem de Arme, a maga sagrada. Magos tem defesa, vida e ataque base reduzidos, mas seu ataque especial é poderoso");
            printf("\nFoi aquirido: Habilidade Especial - %s", userMain->personagem.limitacoes.habilidadeEspecial.nome);
            printf("\n");

            return 3;

            }else{

                printf("\nOcorreu um erro.");
                return 0;

            }

        }

    }

}

void criaMonstro(int *deslogar){

    char resposta[4];
    int erro=0;
    monstro monstroOg = {0};
    monstro monstroCmp = {0};
    FILE *arqMonstros;

    for( ; ; ){

        printf("Deseja criar um novo monstro?");
        printf("\n");
        fflush(stdin);
        fgets(resposta, 4, stdin);

        if( strncmp(strlwr(resposta), "sim", 3) == 0 ){

        printf("\nDigite o nome do seu novo monstro: ");
        fflush(stdin);
        fgets(monstroOg.nomeMonstro, 20, stdin);

        monstroOg.nomeMonstro[strcspn(monstroOg.nomeMonstro, "\n")] = 0;

        printf("\nDigite a vida do seu novo monstro: ");
        scanf("%d", &monstroOg.vida);

        printf("\nDigite o ataque do seu novo monstro: ");
        scanf("%d", &monstroOg.ataque);

        printf("\nDigite a defesa do seu novo monstro: ");
        scanf("%d", &monstroOg.defesa);

        monstroCmp = monstroOg;

        for( ; ; ){

            arqMonstros = fopen("monstros.txt","r");
            if (arqMonstros == NULL){

                    if( access( "monstros.txt", F_OK ) != -1 ) {

                    printf("\nErro ao abrir arquivo, ");
                    break;

                }else{

                    //cria arquivo caso não exista
                    arqMonstros = fopen("monstros.txt","w");

                    //fecha o arquivo para abrí-lo de novo
                    fclose(arqMonstros);

                }

            }else{

            while( fscanf(arqMonstros,"%s %d %d %d\n", monstroOg.nomeMonstro,&monstroOg.vida,&monstroOg.ataque,&monstroOg.defesa) != EOF){

                if( strncmp( strlwr(monstroCmp.nomeMonstro), strlwr(monstroOg.nomeMonstro), sizeof(monstroOg.nomeMonstro)) == 0 ){

                    printf("\nO monstro já existe.");
                    printf("\n");
                    erro = 1;

                }

            }

            if(erro == 1){

                fclose(arqMonstros);
                break;

            }

            arqMonstros = fopen("monstros.txt","a");

            fprintf(arqMonstros,"%s %d %d %d ", monstroCmp.nomeMonstro, monstroCmp.vida, monstroCmp.ataque, monstroCmp.defesa);
            /*
            fprintf(arqMonstros,"%d", monstroOg.vida);
            fprintf(arqMonstros,"%d", monstroOg.ataque);
            fprintf(arqMonstros,"%d", monstroOg.defesa);
            */

            fclose(arqMonstros);
            break;

            }

        }

        }else{

            if(strncmp(strlwr(resposta), "nao", 3) == 0){

                *deslogar = 1;

                system("cls");
                break;

            }else{

                printf("\nComando Inválido.");
                printf("\n");

            }

        }

    }

}

int geraMonstro(monstro *monstroOg){

    FILE *arqMons;
    int i=0, num;

    arqMons = fopen("monstros.txt","r");
    if (arqMons == NULL){

            //caso o arquivo não tenha sido aberto, checa se ele existe
            if( access( "monstros.txt", F_OK ) != -1 ) {

                //caso o arquivo exista, erro ao abrí-lo
                printf("\nErro ao abrir arquivo");
                return 1;

            }else{

                //caso o arquivo não exista, crie o arquivo
                fclose(arqMons);

                arqMons = fopen("monstros.txt","w");

                fclose(arqMons);

            }

    }else{

        srand(time(NULL));

        //escreve os valores do usuário no arquivo save.txt
        while(fscanf(arqMons,"%s %d %d %d\n", monstroOg->nomeMonstro,&monstroOg->vida,&monstroOg->ataque,&monstroOg->defesa) != EOF){

            i++; //lê a quantidade de monstros no arquivo

        }

        //você tem que fechar e abrir o arquivo novamente devido ao fato de que você já está no final do mesmo, isso te leva pro início
        fclose(arqMons);

        //reabrindo o arquivo para checar o valor obtido randomicamente
        arqMons = fopen("monstros.txt","r");

        if(i>1){
        num = rand() % (i-1) + 1; //zero não pode acontecer, então tiramos um valor do total e adicionamos um ao valor randômico criado
        }

        for(i=0; i<num; i++){

            //lêmos o fscanf até o valor gerado
            fscanf(arqMons,"%s %d %d %d\n", monstroOg->nomeMonstro,&monstroOg->vida,&monstroOg->ataque,&monstroOg->defesa);

        }

        fclose(arqMons);

    }

    return 0;

}

void sistemaLevel(usuario *userMain, usuario *espelho){

    if(userMain->personagem.level.level == 0){

        userMain->personagem.level.ptsNec = 100;

    }

    userMain->personagem.level.pts = userMain->personagem.level.pts + 50;

    if(userMain->personagem.level.pts >= userMain->personagem.level.ptsNec){

        printf("\nVocê subiu de nível, todos os seus status aumentaram.");

        //novo status base
        userMain->personagem.ataque = userMain->personagem.ataque * 1.1;
        userMain->personagem.defesa = userMain->personagem.defesa * 1.1;
        userMain->personagem.vida = userMain->personagem.vida * 1.1;
        userMain->personagem.mana = userMain->personagem.mana * 1.2;
        userMain->personagem.limitacoes.habilidadeEspecial.ataque = userMain->personagem.limitacoes.habilidadeEspecial.ataque * 1.3;

        //restaurando status ingame
        espelho->personagem.ataque = userMain->personagem.ataque;
        espelho->personagem.defesa = userMain->personagem.defesa;
        espelho->personagem.vida = userMain->personagem.vida;
        espelho->personagem.mana = userMain->personagem.mana;
        espelho->personagem.limitacoes.habilidadeEspecial.ataque = userMain->personagem.limitacoes.habilidadeEspecial.ataque;

        userMain->personagem.level.level++;
        userMain->personagem.level.ptsNec = userMain->personagem.level.ptsNec * 2.25;

    }

}

void escalarMonstros(monstro *monstroOg, int *progresso){

    monstroOg->ataque = monstroOg->ataque * (0.3 * *progresso);
    monstroOg->defesa = monstroOg->defesa * (0.5 * *progresso);
    monstroOg->vida = monstroOg->vida * (0.4 * *progresso);

}

void batalhaJogo(usuario *userMainOg, int *sair, int *progresso){

    //declara o struct do monstro
    monstro monstroOg;
    usuario userMain;
    userMain = *userMainOg;

    char acao[5]; //ação
    int i, derrota = 0, turno, vidaAt, defesaAt, ataqueAt, manaAt, ataqueTotal; //variáveis auxiliares

    for(i=0;i<5;i++){ //for referente às ordas de monstros

            if(*sair == 1 || derrota == 1){
                system("cls");
                break;

            }

            if(geraMonstro(&monstroOg) == 0){

            if(*progresso > 2){

            escalarMonstros(&monstroOg, progresso);

            }

            //cabeçalho da batalha
            printf("\nVocê encontrou um monstro, prepare-se para a batalha");
            printf("\n");

            for( ; ; ){

                turno=0;

                if(*sair == 1){

                        break;

                }

                if(userMain.personagem.vida <= 0){

                    derrota = 1;
                    break;

                }

                if(monstroOg.vida <= 0 ){

                    sistemaLevel(userMainOg, &userMain);

                    printf("\nO monstro %c%s foi derrotado, você recupera parte de sua vida e mana", toupper(monstroOg.nomeMonstro[0]), monstroOg.nomeMonstro + 1);
                    printf("\n");

                    userMain.personagem.vida = userMain.personagem.vida + ( 0.3 * userMainOg->personagem.vida );
                    userMain.personagem.mana = userMain.personagem.mana + ( 0.2 * userMainOg->personagem.mana );

                    break;

                }

                for( ; ; ){

                    printf("\nSeus stats atuais");
                    printf("\nvida: %d, mana: %d, ataque: %d, defesa: %d", userMain.personagem.vida, userMain.personagem.mana, userMain.personagem.ataque, userMain.personagem.defesa);
                    printf("\n");
                    printf("\nStats de %c%s", toupper(monstroOg.nomeMonstro[0]), monstroOg.nomeMonstro + 1);
                    printf("\nvida: %d, ataque: %d, defesa %d", monstroOg.vida, monstroOg.ataque, monstroOg.defesa);
                    printf("\n");

                    printf("\nDigite sua ação, sendo ela ataque ou habilidade especial");
                    printf("\n(Para tal, digite atq ou he)");
                    printf("\n");
                    fflush(stdin);
                    fgets(acao, 5, stdin);

                    if(strncmp( strlwr(acao) , "he", 2) == 0){

                        //remove a mana utilizada

                        manaAt = userMain.personagem.mana;
                        userMain.personagem.mana = userMain.personagem.mana - userMain.personagem.limitacoes.habilidadeEspecial.mana;

                        if(userMain.personagem.mana < 0){

                            userMain.personagem.mana = manaAt;
                            printf("\nVocê não tem mana suficiente");

                        }else{

                        turno++;

                        system("cls");

                        //guarda os valores originais de antes do turno
                        vidaAt = monstroOg.vida;
                        defesaAt = monstroOg.defesa;
                        ataqueAt = userMain.personagem.limitacoes.habilidadeEspecial.ataque;

                        //defesa igual a ataque subtraído da defesa
                        monstroOg.defesa = monstroOg.defesa - userMain.personagem.limitacoes.habilidadeEspecial.ataque;

                        if(monstroOg.defesa > 0){

                            printf("\nA defesa deste monstro é muito alta!");

                        }else{

                            //caso negativo, adiciona o mesmo, não deve-se curar ninguém
                            userMain.personagem.limitacoes.habilidadeEspecial.ataque = userMain.personagem.limitacoes.habilidadeEspecial.ataque + monstroOg.defesa;

                            monstroOg.vida = monstroOg.vida + monstroOg.defesa;
                            monstroOg.defesa = defesaAt;
                            userMain.personagem.limitacoes.habilidadeEspecial.ataque = ataqueAt;

                            printf("%c%s recebe %d de dano", toupper(monstroOg.nomeMonstro[0]), monstroOg.nomeMonstro + 1, vidaAt - monstroOg.vida);

                        }

                        break;

                        }

                    }

                    if(strncmp( strlwr(acao) , "atq", 3) == 0){

                        turno++;

                        system("cls");

                        vidaAt = monstroOg.vida;
                        defesaAt = monstroOg.defesa;
                        ataqueAt = userMain.personagem.ataque;
                        ataqueTotal = userMain.personagem.ataque + userMain.personagem.limitacoes.armaEspecifica.ataque;

                        monstroOg.defesa = monstroOg.defesa - ataqueTotal;

                        if(monstroOg.defesa > 0){

                            printf("\nA defesa deste monstro é muito alta!");

                        }else{

                            ataqueTotal = userMain.personagem.ataque + monstroOg.defesa;

                        }

                        //remove vida do monstro
                        monstroOg.vida = monstroOg.vida + monstroOg.defesa;
                        monstroOg.defesa = defesaAt;
                        userMain.personagem.ataque = ataqueAt;

                        printf("%c%s recebe %d de dano", toupper(monstroOg.nomeMonstro[0]), monstroOg.nomeMonstro + 1, vidaAt - monstroOg.vida);

                        userMain.personagem.mana = userMain.personagem.mana + (0.1 * userMainOg->personagem.mana);

                        if(userMain.personagem.mana > userMainOg->personagem.mana){

                            userMain.personagem.mana = userMainOg->personagem.mana;

                        }else{

                        }

                        break;

                    }

                    if( strncmp( strlwr(acao) , "sair", 4 ) == 0){

                        *sair = 1;
                        break;

                    }

                }

                    if(turno > 0){

                        vidaAt = userMain.personagem.vida;
                        userMain.personagem.vida = userMain.personagem.vida - monstroOg.ataque;
                        printf("\nVocê recebe %d de dano", vidaAt - userMain.personagem.vida);
                        printf("\n");

                    }


            }


        }else{

            printf("\nErro ao gerar monstro");

        }

        if(i == 4){

            *progresso = *progresso + 1;

        }

    }

    if(derrota == 1){

        printf("\nVocê perdeu. Volte ao checkpoint.");
        printf("\n");

        Sleep(2000);
        system("cls");

    }

}

void textosJogo(int *progresso){

    //essa função contém todos os textos do jogo

    if(*progresso == 1){
    //texto inicial da primeira vez jogando
    printf("Bem-vindo ao RPG Fatec\n");
    printf("Você foi deixado à mercê do mundo real e suas dificuldades; porém, não deverá temer.\n");
    printf("Você foi o escolhido por Roger, o guerreiro mais renomado de seu bairro vizinho\n");
    printf("Sem ideia do que fazer, Roger te deu uma missão. Encontrar o místico Giancarlo, que foi encontrado correndo em um reino bem distante\n");
    }

    if(*progresso == 2){
    //texto quando você acaba de escolher sua classe
    printf("\nVocê encontrou seu primeiro monstro. O jogo se baseia em monstros consecutivos.");
    printf("\nA cada 5 monstros derrotados, você passa de orda");
    }

    if(*progresso == 3){

    printf("\nPelo visto já entendeu como o jogo funciona, agora a cada orda os monstros ficam mais fortes.");
    printf("\nCreio que não lhe devo explicações se não o fato de como o jogo escala conforme o seu nível");
    printf("\nSe comporte e se divirta");

    }



}

int salvar(usuario *userMain){

    FILE *arqSave;

    for( ; ; ){

        arqSave = fopen("save.txt","a");
        if (arqSave == NULL){

                //caso o arquivo não tenha sido aberto, checa se ele existe
                if( access( "save.txt", F_OK ) != -1 ) {

                    //caso o arquivo exista, erro ao abrí-lo
                    printf("\nErro ao abrir arquivo, ");
                    return 1;

                }else{

                    //caso o arquivo não exista, crie o arquivo
                    fclose(arqSave);

                    arqSave = fopen("save.txt","w");

                    fclose(arqSave);

                }

        }else{

            //escreve os valores do usuário no arquivo save.txt
            fwrite(userMain, sizeof(usuario), 1, arqSave);
            fclose(arqSave);
            return 0;

        }

    }

}

void escolhaClasse(usuario *userMain, int *classeEscolhida, int *progresso){

    for( ; ; ){

        printf("\nEscolha sua classe para iniciar.\n\nGuerreiro || Arqueiro || Mago\n\n");
        fflush(stdin); //limpar o cache do teclado
        fgets(userMain->personagem.limitacoes.nomeClasse, 40, stdin); //pede um valor a ser digitado e recebe a string

        if(checaClasse(classeEscolhida, userMain) > 0){ //checa a classe que você escolheu e atribui os valores e items iniciais ao seu personagem

            *progresso = 2;
            userMain->progresso = *progresso;

            if( salvar(userMain) == 0 ){; //processo para salvar as escolhas do personagem

                break; //sai da função for caso essa escolha tenha sido salva de forma correta

            }else{

                printf("\nOcorreu um erro ao salvar");

            }

        }else{

            printf("\nComando inválido, digite a classe que pretende se tornar corretamente\n");

        }

    }

}

void inicioJogo(usuario *userMain, int *classeEscolhida, int *progresso, int *sair){

    for( ; ; ){

        if(*progresso == 1){

        textosJogo(progresso);
        escolhaClasse(userMain, classeEscolhida, progresso);

        }

        if(*progresso == 2){

        textosJogo(progresso);
        batalhaJogo(userMain, sair, progresso);

        }

        if(*progresso == 3){

        textosJogo(progresso);
        batalhaJogo(userMain, sair, progresso);

        }

        if(*progresso >= 4){

        batalhaJogo(userMain, sair, progresso);

        }

        if(*sair == 1){

            break;

        }

    }

}

void checaSave(usuario *userMain, save *save, int *progresso){

    FILE *arqSave;
    int erro=0;

    arqSave = fopen("save.txt" ,"r");
    if (arqSave == NULL){

        if( access( "save.txt", F_OK ) != -1 ) {

        //caso o arquivo exista, erro ao abrí-lo
        printf("\nFalha ao abrir o progresso salvo.");

        }else{

        *progresso = 1;
        erro=0;

        }

    }else{

        while( fread(save, sizeof(usuario), 1, arqSave) == 1 ){

            if( strncmp ( strlwr(save->saveDoUsuario.login), strlwr(userMain->login), strlen(userMain->login) ) == 0 ){

                *userMain = save->saveDoUsuario;
                erro=0;

            }else{

                *progresso = 1;
                erro=0;

            }

        }

        if(erro == 0){

            *progresso = 1;

        }

        fclose(arqSave);

    }

}

int realizaLogin(usuario *userMain){

    char usuarioTemp[20] = {0};
    char senhaTemp[20] = {0};
    int erro;

    //pede o usuário e armazena em uma variável
    printf("\nDigite seu usuário: ");
    fflush(stdin);
    fgets(usuarioTemp, 20, stdin);
    usuarioTemp[strcspn(usuarioTemp, "\n")] = 0;

    //pede a senha e armazena em uma variável
    printf("\nDigite sua senha: ");
    fflush(stdin);
    fgets(senhaTemp, 20, stdin);
    senhaTemp[strcspn(senhaTemp, "\n")] = 0;

    FILE *arqUsuarios;

    arqUsuarios = fopen("usuarios.txt","r");
    if (arqUsuarios == NULL){

            printf("\nErro ao abrir arquivo");

    }else{

        //deve-se subtrair o tamanho do personagem pois o arquivo em questão não os contém
        while( fread(userMain->login, 40, 1, arqUsuarios) == 1 ){

            if( strncmp ( strlwr(userMain->login) , strlwr(usuarioTemp), strlen(usuarioTemp) ) == 0 )  {

               if( strncmp ( strlwr(userMain->senha) , strlwr(senhaTemp), strlen(usuarioTemp) ) == 0 ) {

                    printf("\nLogin realizado com sucesso.");
                    return 0;

               }

            }else{

                erro = 1;

            }

        }

    if (erro == 1){

        printf("\nOcorreu um erro. Usuário ou senha errados.");
        Sleep(1000);
        system("cls");

    }

    fclose(arqUsuarios);

    }

    return 1;
}

int checaUsuario(char usuarioTemp[20], usuario *userMain){

    FILE *arqUsuarios;
    int error;

    arqUsuarios = fopen("usuarios.txt","r");
    if (arqUsuarios == NULL){

        if( access( "usuarios.txt", F_OK ) != -1 ) {

            printf("\nErro ao abrir arquivo, ");
            return 1;

        }else{

            printf("\nArquivo não existe, criando arquivo");
            fclose(arqUsuarios);

            arqUsuarios = fopen("usuarios.txt","w");



            fclose(arqUsuarios);

        }

    }else{

        while( fread(&userMain->login, sizeof(userMain->login), 1, arqUsuarios) == 1 ){

            if( strncmp ( strlwr(userMain->login) , strlwr(usuarioTemp), strlen(usuarioTemp) ) == 0){

                error=1;
                break; //para a função while no mento em que um erro for encontrado

            }else{

                error=0;

            }

        }

        //checando erros
        if(error == 1){

            printf("\nO usuário já existe, ");
            return 1;

        }


        //ler o save implementado mais tarde
        fclose(arqUsuarios);

    }

    return 0;

}

void aplicaValores(usuario *userMain){

    FILE *arqUsuarios;

    arqUsuarios = fopen("usuarios.txt","a");
    if (arqUsuarios == NULL){

            printf("\nErro ao abrir arquivo");

    }else{

    fwrite(userMain->login, sizeof(userMain->login), 1, arqUsuarios); //armazena usuario
    fwrite(userMain->senha, sizeof(userMain->senha), 1, arqUsuarios); //armazena senha
    fclose(arqUsuarios);

    }

}

void criaLogin(usuario *userMain){

    char usuarioTemp[20] = {0}; //variável temporária para checagem de dados

    for( ; ; ){

        printf("\nDigite o seu novo Usuário: ");
        fflush(stdin);
        fgets(usuarioTemp, 20, stdin);

        usuarioTemp[strcspn(usuarioTemp, "\n")] = 0;

        //validações do usuário
        if( checaUsuario(usuarioTemp, userMain) == 0 ){

            strncpy(userMain->login, usuarioTemp, 20);

            //relacionado à senha do usuário
            printf("\nDigite a nova senha: ");
            fflush(stdin);
            fgets(userMain->senha, 20, stdin);

            userMain->senha[strcspn(userMain->senha, "\n")] = 0;

            aplicaValores(userMain);
            break;


        }else{

            printf("ocorreu um erro, tente novamente");

        }

    }

}

void sistemaLogin(usuario *userMain, int *sair){

    char resposta[5];
    char sim[3] = "sim";
    char nao[3] = "nao";
    char sairJogo[4] = "sair";

    for( ; ; ){
        printf("Você pode optar por sair do jogo digitando \"sair\" sem as aspas");
        printf("\nVocê ja possui um cadastro? (Sim/Nao): ");
        fflush(stdin);
        fgets(resposta, 5, stdin);

        if( strncmp( strlwr(resposta) , nao, 3) == 0 ){

        criaLogin(userMain);

        }else{

            if( strncmp( strlwr(resposta) , sim, 3) == 0 ){

            if( realizaLogin(userMain) == 0){

            Sleep(2000); //aguarda 2 segundos
            system("cls");
            break;

            }

            }else{

                if( strncmp( strlwr(resposta) , sairJogo, 4) == 0 ){

                *sair = 1;
                break;

                }else{

                printf("Resposta inválida, tente novamente");
                system("cls");

                }
            }
        }
    }
}

void limparStruct(usuario *userMain){

    memset(userMain, 0, sizeof(usuario));

}

int main(){

    //declaração de variáveis
    usuario userMain = {0}; //atribui um valor nulo à todas as variáveis dentro do struct para inicializar, removendo lixo da memória
    save save = {0};
    int classeEscolhida, progresso=0, sair, deslogar; //progresso é a variável utitlizada pra marcar em que parte da história o usuário se encontra

    //a linguagem se torna português e tem suporte à acentos
    setlocale(LC_ALL, "portuguese");

    for( ; ; ){

        if(deslogar == 1){

            limparStruct(&userMain);
            progresso = 0;
            deslogar = 0;

        }

        if( ( (progresso < 1) && (userMain.login[0] == '\0') ) || deslogar == 1 ){
        //sistema de login
        sistemaLogin(&userMain, &sair);
        }

        if(sair == 1){

            break;

        }

        if( strncmp( strlwr(userMain.login), "admin", 5) == 0){

            criaMonstro(&deslogar);

        }else{

        //checa se um save já existe nos arquivos do jogo
        checaSave(&userMain, &save, &progresso);

        if(userMain.progresso>0){

            progresso = userMain.progresso;

        }


        //começa o jogo dependendo do especificado no arquivo save

        inicioJogo(&userMain, &classeEscolhida, &progresso, &deslogar);


        }

    }


    return 0;
}
