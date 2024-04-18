
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>


using namespace std;


int main(){


	key_t key;
	int shmid;
	const char* path = "root";
	int id = 'A';

	int n;
	bool game = true;
	cout<<"Enter a for the grid size: ";
	cin>>n;

	size_t size = sizeof(int) * n * n;

	key = ftok(path,id);
	shmid = shmget(key, size, IPC_CREAT | 0666);
	if(shmid == -1){
		cout<< "Error: shmget failed" << endl;
		return 1;
	}
	char* shared_memory = (char*) shmat(shmid, nullptr, 0);
	if(shared_memory == (char*) -1) {
		cout<<" Error: shmat failed" <<endl;
		return 1;
	}
	memset(shared_memory, 0,size);
	char grid[n][n];
	for(int i = 0; i<n;i++){
		for(int j = 0; j<n;j++){
			grid[i][j] = '-';
		}

	}
	grid[0][0] = char(n);
	memcpy(shared_memory, grid, size);





	bool winner = false;
	bool loser = false;
	bool draw = false;
	int x, y;


	while(game){
		//checking if player two lost
		if(shared_memory[0] == 'O') loser = true;
		//if player two lost break out of the wile loop
		if(loser){
			cout<< "player one lost"<<endl;
			break;
		}

		//checking for draw
		for(int i = 0; i<n;i++){
			for(int j = 0; j<n;j++){
				if(shared_memory[i*n+j] == char(n) || shared_memory[i*n+j] == '-'){
					draw = false;
					i= n;
					break;

				}else{
					draw = true;
				}
			}
		}
		if(draw && (!winner) ){
			cout<<"The game was a draw"<<endl;
			break;
		}
		//continue the game if the game is not won

		if(!winner){

			//print out the grid
			for(int i = 0; i<n;i++){
				for(int j = 0; j<n;j++){
					if(shared_memory[i*n+j] == char(n)){
						cout << "- ";
					}else{
						cout<< shared_memory[i*n+j]<<" ";
					}
				}
				cout<<endl;
			}
			//take input from the user
			cout<<"Player 1 enter the x coordinate: ";
			cin>>x;
			if(cin.fail()){
				cout<<"You have entered a non integer value"<<endl;
				cout<<"please input an integer from 0 to "<< n-1<<endl;
				cin.clear();
				cin.ignore(1000,'\n');
				continue;
			}
			cout<<"Enter the y coordinate: ";
			cin>>y;

			if(cin.fail()){
				cout<<"You have entered a non integer value"<<endl;
				cout<<"please input an integer from 0 to "<< n-1 <<endl;
				cin.clear();
				cin.ignore(1000,'\n');
				continue;
			}

		}else{
			cout<<"player one won"<<endl;
			break;
		}
		//checking for proper user input and updating the shared memory
		if(x>n || y>n || y<0 || x<0){
			cout<<"you have entered an integer outside the grid"<<endl;
			cout<<"please input an integer from 0 to "<<n-1 <<endl;
			continue;
		}
		if(shared_memory[x*n+y] != 'o'){

			shared_memory[x*n+y] = 'x';
		}else{
			cout<<"current coordinate had been taken by player two"<<endl;
			continue;
		}

		//checking for winner after the user input
		for(int i = 0; i<n;i++){
			if(shared_memory[i*n+i]!='x'){

				winner = false;
				break;
			}else{
				winner = true;

			}


		}
		int k = 0;
		int l = n-1;
		if(winner){

			for(int i=0; i<n;i++){
				for(int j = 0; j<n; j++){
					if(shared_memory[i*n+j] == char(n)){
						cout << "- ";
					}else{
						cout<< shared_memory[i*n+j]<<" ";
					}

				}
				cout<<endl;
			}

			shared_memory[0] = 'X';
			continue;


		}
		while(k<n){
			if(shared_memory[k*n+l]!='x'){
				winner = false;
				break;
			}else{
				winner = true;
			}
			k++;
			l--;
		}
		if(winner){

			for(int i=0; i<n;i++){
				for(int j = 0; j<n; j++){

					if(shared_memory[i*n+j] == char(n)){
						cout << "- ";
					}else{
						cout<< shared_memory[i*n+j]<<" ";
					}
				}
				cout<<endl;
			}

			shared_memory[0] = 'X';
			continue;


		}
		for(int i = 0; i<n;i++){
			if(shared_memory[x*n+i]!='x'){
				winner = false;
				break;
			}else{
				winner = true;
			}
		}
		if(winner){

			for(int i=0; i<n;i++){
				for(int j = 0; j<n; j++){

					if(shared_memory[i*n+j] == char(n)){
						cout << "- ";
					}else{
						cout<< shared_memory[i*n+j]<<" ";
					}

				}
				cout<<endl;
			}

			shared_memory[0] = 'X';
			continue;


		}
		for(int i = 0; i<n;i++){
			if(shared_memory[i*n+y]!='x'){
				winner = false;
				break;
			}else{
				winner = true;
			}
		}

		if(winner){
			for(int i=0; i<n;i++){
				for(int j = 0; j<n; j++){

					if(shared_memory[i*n+j] == char(n)){
						cout << "- ";
					}else{
						cout<< shared_memory[i*n+j]<<" ";
					}

					

				}
				cout<<endl;
			}
			shared_memory[0] = 'X';
			continue;
		}
	}


	shmdt(shared_memory);
	//only remove the shared memory if player one is the loser
	if(loser || draw){
		 int result = shmctl(shmid, IPC_RMID, NULL);
		if(result == -1){
			cout<< "Error: shmctl failed"<<endl;
			return 1;
		}
	}
	return 0;
}


