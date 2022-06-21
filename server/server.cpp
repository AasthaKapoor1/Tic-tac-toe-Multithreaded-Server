#include <bits/stdc++.h>
#include <sys/socket.h>
#include <limits.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define SERVERPORT 8989
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 100  // number of waiting collenction the server allows
#define THREAD_POOL_SIZE 20 // number of threads in the server

pthread_t thread_pool[THREAD_POOL_SIZE];                         // fixed number of threads
pthread_mutex_t lock_current_player = PTHREAD_MUTEX_INITIALIZER; // mutex locks
pthread_mutex_t play = PTHREAD_MUTEX_INITIALIZER; // mutex locks
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

void *handle_connection(void *p_client_socket);
int check(int exp, const char *msg);
int THREADNO = 0;
bool turnx = true;

char game[3][3];

string convert_to_string(char game[3][3])
{
    string state;
    for (int i = 0; i < 3; i++)
    {
        state.push_back('|');
        for (int j = 0; j < 3; j++)
        {
            state.push_back(game[i][j]);
            state.push_back('|');
        }
        state += "\n";
    }
    return state;
}

int main(int argc, char **argv)
{
    int server_socket, client_socket, addr_size;
    SA_IN server_addr, client_addr;

    // initialising the game
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            game[i][j] = '-';
        }
    }

    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create socket");
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVERPORT);

    check((bind(server_socket, (SA *)&server_addr, sizeof(server_addr))), "Bind Failed!");

    check(listen(server_socket, SERVER_BACKLOG), "Listen Failed!");

    while (true)
    {
        cout << "Waiting for connection\n";
        addr_size = sizeof(SA_IN);
        check(client_socket = accept(server_socket, (SA *)&client_addr, (socklen_t *)&addr_size), "accept failed!!");

        cout << ("Connected!\n");
        // pthread_mutex_init(&lock_current_player, NULL);

        int *pclient = (int *)malloc(sizeof(int));
        *pclient = client_socket;
        pthread_create(&thread_pool[THREADNO++], NULL, handle_connection, (void *)pclient);
    }

    return 0;
}

int check(int exp, const char *msg)
{
    if (exp == SOCKETERROR)
    {
        perror(msg);
        exit(1);
    }
    return exp;
}

int win(char game[3][3])
{
    int win=0;
    for (int i = 0; i < 3; i++)
    {
        if (game[i][0] == game[i][1] && game[i][1] == game[i][2] && game[i][0] != '-')
        {
            if(game[i][0]=='X'){
                win=1;
            }
            else{
                win=2;
            }
            return win;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (game[0][i] == game[1][i] && game[1][i] == game[2][i] && game[0][i] != '-')
        {
            if(game[0][i]=='X'){
                win=1;
            }
            else{
                win=2;
            }
            return win;
        }
    }
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[0][0] != '-')
    {
        if(game[0][0]=='X'){
                win=1;
            }
            else{
                win=2;
            }
            return win;
    }
    if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[2][0] != '-')
    {
        if(game[2][0]=='X'){
                win=1;
            }
            else{
                win=2;
            }
            return win;
    }

    return win;
}

void make_move(char buffer[])
{
    pthread_mutex_lock(&lock_current_player);
    if (turnx)
    {
        game[buffer[0] - 48][buffer[1] - 48] = 'X';
        turnx = false;
    }
    else
    {
        game[buffer[0] - 48][buffer[1] - 48] = 'O';
        turnx = true;
    }
    pthread_mutex_unlock(&lock_current_player);
}

void *handle_connection(void *p_client_socket)
{
    int client_socket = *((int *)p_client_socket);
    free(p_client_socket);
    char buffer[BUFSIZE];

    size_t bytes_read;
    int msgsize = 0;
    bool w = true;
    memset(buffer, '\0', BUFSIZE);

    while (true)
    {
        // pthread_mutex_lock(&lock_current_player);
        string temp1 = convert_to_string(game);
        temp1 += "\0";
        memset(buffer, '\0', BUFSIZE);
        int ind1 = 0;
        for (int i = 0; i < temp1.size(); i++)
        {
            buffer[ind1++] = temp1[i];
        }
        write(client_socket, buffer, BUFSIZE);
        // pthread_mutex_unlock(&lock_current_player);

        memset(buffer, '\0', BUFSIZE);

        read(client_socket, buffer, sizeof(buffer)); // reading input from client

        if (turnx)
        {
            cout << "Player X's move : " << buffer[0] << buffer[1] << endl;
        }
        else
        {
            cout << "Player O's move : " << buffer[0] << buffer[1] << endl;
        }


        make_move(buffer);
        string temp = convert_to_string(game);
        // temp += "\0";
        memset(buffer, '\0', BUFSIZE);
        int ind = 0;
        for (int i = 0; i < temp.size(); i++)
        {
            buffer[ind++] = temp[i];
        }


        if (win(game) > 0)
        {
            string msg;
            if(win(game) == 1){ msg = "Player_X_WON\n";}
            else{msg = "Player_O_WON\n";}
            msg += "\0";
            for(int i=0; i<msg.size(); i++){
                buffer[ind++] = msg[i];
            }
            write(client_socket, buffer, BUFSIZE);
            
            break;
        }
        else{
            // pthread_mutex_lock(&lock_current_player);
            string msg;
            if(turnx){
                msg = "Wait_for_X\n";
                msg += "\0";
            }
            else{
                msg = "Wait_for_O\n";
                msg += "\0";
            }
            for(int i=0; i<msg.size(); i++){
                buffer[ind++] = msg[i];
            }
            // pthread_mutex_unlock(&lock_current_player);
        }
        // else{
        //     char ingame[] = "1";
        //     write(client_socket, ingame, 1);
        // }
        write(client_socket, buffer, BUFSIZE);


        memset(buffer, '\0', BUFSIZE);
        cout << "one request done" << endl;
    }
    close(client_socket);

    cout << ("Closing connection\n");
    return NULL;
}
