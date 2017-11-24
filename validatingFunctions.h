bool checkNumberOfPlayers(int n){
	if(n<2) return false;
	else return true;
}

bool checkNumberOfPenguins(int n, int k){
	//n is the parameter of available penguins, k is number of fields on the map (rows*columns)//
	if(n>=k) return false;
	else return true;
}

bool checkNumberOfRows(int n){
	if(n<2) return false;
	else return true;
}

bool checkNumberOfColumns(int n){
	if(n<2) return false;
	else return true;
}

bool checkScoreOfPlayer(int score, int sum){
	//score is simply the score(of each player), sum is the sum of scores of all players//
	if((score<0)||(score>sum)) return false;
	else return true;
}

bool checkFieldProperty(int field, int n){
	//field is value of field, n is number of players//
	if((field>3)||(field<(-1)*n)) return false;
	else return true;
}


