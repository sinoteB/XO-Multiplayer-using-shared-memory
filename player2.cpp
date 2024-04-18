
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
using namespace std;


int main(){

	cout<<"Make sure you run the player1 source code for proper gaming experiance!"<<endl;

	key_t key;
	int shmid;
	const char* path = "root";
	int id = 'A';

	int n;
	bool game = true;
	key = ftok(path,id);
	shmid = shmget(key, 0,0);
	if(shmid == -1){
		cout<< "Error: shmget failed" << endl;
		return 1;
	}
	char* n_ptr = (char*) shmat(shmid, nullptr, 0);
	if(n_ptr == (char*) -1) {
		cout<<" Error: shmat failed" <<endl;
		return 1;
	}
	n = *n_ptr;
	cout<<"size of grid is: " << n<<endl;
	char* shared_memory = n_ptr;

	int x, y;
	bool winner = false;
	bool loser = false;
	bool draw = true;

	while(game){
		//checking if player two lost
		if(shared_memory[0]=='X') loser = true;
		//if player two lost break out of the while loop
		if(loser){
			cout<< "player two lost" << endl;
			break;
		}
		//checking for draw
		for(int i = 0; i<n;i++){
			for(int j = 0; j<n; j++){
				if(shared_memory[i*n+j] == '-' || shared_memory[i*n+j] == char(n)){
					draw = false;
					i=n;
					break;
				}else{
					draw = true;
				}
			}
		}
		//if it is a draw end the game
		if(draw && (!winner)){
			cout<<"The game was a draw"<<endl;
			break;
		}
		//continue playing the game if it is not a won
		if(!winner){

			cout<<"Player 2 enter the x coordinate: ";
			cin>>x;
			if(cin.fail()){
				cout<<"You have entered a non integer value"<<endl;
				cout<<"please input an in integer from 0 to "<<n-1<<endl;
				cin.clear();
				cin.ignore(1000,'\n');
				continue;
			}
			cout<<"Enter the y coordinat: ";
			cin>>y;

			if(cin.fail()){

				cout<<"You have entered a non integer value"<<endl;
				cout<<"please input an integer from 0 to "<<n-1<<endl;
				cin.clear();
				cin.ignore(1000,'\n');
				continue;
			}
		}else{
			cout<<"player two won"<<endl;
			break;
		}
		//checking for proper user inpute and updating the shared memory
		if(x>n || y>n || y<0 || x<0){
			cout<<"you have entered an interger outside the grid"<<endl;
			cout<<"please input an integer from 0 to "<<n-1<<endl;
			continue;
		}
		if(shared_memory[x*n+y] != 'x'){
			shared_memory[x*n+y] = 'o';
		}else{
			cout<<"current coordinate had been taken by player one"<<endl;
			continue;
		}

		//checking for winner after each move
		for(int i = 0; i<n;i++){
			if(shared_memory[i*n+i] != 'o'){
				winner = false;
				break;
			}else{
				winner = true;
			}
		}

		int k = 0;
		int l = n-1;
		if(winner){
			shared_memory[0] = 'O';
			continue;
		}
		while(k<n){
			if(shared_memory[k*n+l] != 'o'){
				winner = false;
				break;
			}else{
				winner = true;
			}
			k++;
			l--;
		}
		if(winner){
			shared_memory[0] = 'O';
			continue;
		}
		for(int i = 0; i<n; i++){
			if(shared_memory[x*n+i] != 'o'){
				winner = false;
				break;
			}else{
				winner = true;
			}

		}
		if(winner){
			shared_memory[0] = 'O';
			continue;
		}
		for(int i = 0; i<n; i++){
			if(shared_memory[i*n+y] != 'o'){
				winner = false;
				break;
			}else{
				winner = true;
			}

		}
		//sending a message to player one that they lost
		if(winner){
			shared_memory[0] = 'O';
			continue;
		}
	}
	shmdt(shared_memory);
	shmdt(n_ptr);
	//only remove the shared memory if player two is the loser 
	if(loser){
		 int result = shmctl(shmid, IPC_RMID, NULL);
		if(result == -1){
			cout<< "Error: shmctl failed"<<endl;
			return 1;
		}
	}
	return 0;
}


