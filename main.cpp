/************************************************************************************************
*Program Filename: CS_162_Final_smitcoli.cpp
*Author: Colin Smith
*Date: 6/05/2014
*Description: Text battle program between two characters using a random number generator. This
*program uses a tournament format.
*Input: creature choices for each players team, team confirmation
*Output: character stats and rolls. Results of battle. Results of tournament
*Class: CS 162
*Due Date: 6/08/2014
*Final
*************************************************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>      //for random number generator
#include <stdlib.h>     //for random number generator
#include <time.h>       //for random number generator
#include <vector>
#include <deque>
#include <stack>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::deque;
using std::stack;

//can be used to determine how many creatures each team gets
int MAXTEAMSIZE = 4;



//Abstract base class
class Creature
{
public:

    //default constructor
    Creature ()
    {
        this->attackRolls = 0;
        this->attackDice = 0;
        this->defenseRolls = 0;
        this->defenseDice = 0;
        this->armor = 0;
        this->HP = 0;
        this->name = "";
    }

    //constructor
    Creature (int attackRolls, int attackDice = 0, int defenseRolls = 0,
              int defenseDice = 0, int armor = 0, int HP = 0, string name = "", string specialAbility = "")
    {
        this->attackRolls = attackRolls;
        this->attackDice = attackDice;
        this->defenseRolls = defenseRolls;
        this->defenseDice = defenseDice;
        this->armor = armor;
        this->HP = HP;
        this->name = name;
    }

    //accessor functions start with the word "get"

    //gets total attack for a combatant
    virtual int getAttack ()
    {
        int attackSum = RNG(this->attackRolls, this->attackDice);

        return attackSum;
    }

    //gets total defense for a combatant
    virtual int getDefense ()
    {
        int defenseSum = RNG (this->defenseRolls, this->defenseDice);

        return defenseSum;
    }

    //this function determines the damage a creature will take
    virtual int calculateHP (int attackSum, int defenseSum, int remainingHealth)
    {
        attackSum = attackSum - (defenseSum + this->armor);

        if (attackSum < 0)
        {
             attackSum = 0;
        }

        remainingHealth = remainingHealth - attackSum;
        return remainingHealth;

    }

    // all functions starting with "set" are mutator functions
    void setAttackRolls (int newAttackRolls)
    {
        this->attackRolls = newAttackRolls;
    }

    void setAttackDice (int newAttackDice)
    {
        this->attackDice = newAttackDice;
    }

    void setDefenseRolls (int newDefenseRolls)
    {
        this->defenseRolls = newDefenseRolls;
    }

    void setDefenseDice (int newDefenseDice)
    {
        this->defenseDice = newDefenseDice;
    }

    void setArmor (int newArmor)
    {
        this->armor = newArmor;
    }

    void setHP (int newStrengthPoints)
    {
        this->HP = newStrengthPoints;
    }

    void setNumberOfWins (int newNumberOfWins)
    {
        this->numberOfWins = newNumberOfWins;
    }


    void setName (string newName)
    {
        this->name = newName;
    }

    void setTeam (string newTeam)
    {
        this->team = newTeam;
    }

    void setReviveSet (int newReviveSet)
    {
        this->reviveSet = newReviveSet;
    }


    //all functions starting with "get" are accessor functions
    int getAttackRolls () const
    {
        return attackRolls;
    }

    int getAttackDice () const
    {
        return attackDice;
    }

    int getDefenseRolls () const
    {
        return defenseRolls;
    }

    int getDefenseDice () const
    {
        return defenseDice;
    }

    int getArmor () const
    {
        return armor;
    }

    int getHPs () const
    {
        return HP;
    }

    int getNumberOfWins () const
    {
        return numberOfWins;
    }

    string getName () const
    {
        return name;
    }

    string getTeam () const
    {
        return team;
    }
    //prints a creatures stats
    void printAll ()
    {
      cout <<"Name: "<<this->name<<endl;
      cout <<"Attack rolls: "<<this->attackRolls<<endl;
      cout <<"Attack dice: "<<this->attackDice<<endl;
      cout <<"Defense rolls: "<<this->defenseRolls<<endl;
      cout <<"Defense dice: "<<this->defenseDice<<endl;
      cout <<"Armor: "<<this->armor<<endl;
      cout <<"HP: "<<this->HP<<endl;
      cout <<"Special Ability: "<<this->specialAbility<<endl;
    }

    //this function gets redefined in the Reptilian class
    int RNG (const int diceRolls, const int diceSize);



//protected member variables given to the child classes
protected:
    int attackRolls;
    int attackDice;
    int defenseRolls;
    int defenseDice;
    int armor;
    int HP;
    int val;
    int numberOfWins;
    string name;
    string team;
    string specialAbility;
    bool reviveSet = false;     //ensure the barbarian only revives once (unlike the zombie)
};

class Goblin : public Creature
{
public:

    //default constructor
    Goblin (int attackRolls = 4, int attackDice = 9, int defenseRolls = 2,
            int defenseDice = 6, int armor = 6, int HP = 10, string name = "Goblin",
            string specialAbility = "Health Regeneration - regenerates health after getting attacked."
            "Can only regenerate up to 4 health per turn and cannot exceed max health"):
            Creature (attackRolls, attackDice, defenseRolls, defenseDice,
                      armor, HP, name, specialAbility)

    {
        this->attackRolls = attackRolls;
        this->attackDice = attackDice;
        this->defenseRolls = defenseRolls;
        this->defenseDice = defenseDice;
        this->armor = armor;
        this->HP = HP;
        this->name = name;
        this->specialAbility = specialAbility;
    }

    //this is the overridden function for goblin class. It adds a health regeneration
    //feature
    virtual int calculateHP (int attackSum, const int defenseSum, int remainingHealth)
    {
        //int remainingHealth;
        int regeneratedHealth;

        attackSum = attackSum - (defenseSum + this->armor);

        if (attackSum < 0)
        {
             attackSum = 0;
        }

        remainingHealth = remainingHealth - attackSum;
        cout <<"Regenerating health."<<endl;
        cout <<endl;

        regeneratedHealth = RNG (1 , 4);

        cout <<this->name<<" has regenerated "<<regeneratedHealth<<" health!"<<endl;
        cout <<endl;

        remainingHealth = remainingHealth +regeneratedHealth;

        if (remainingHealth >= this->HP)
        {
            remainingHealth = this->HP;
        }


        return remainingHealth;

    }

};

class Ogre : public Goblin
{
public:

     //default constructor
    Ogre (int attackRolls = 2, int attackDice = 15, int defenseRolls = 2,
            int defenseDice = 8, int armor = 0, int HP = 25, string name = "Ogre",
            string specialAbility = "Health Regeneration - regenerates health after getting attacked."
             "Can only regenerate up to 5 health per turn and cannot exceed max health"):
            Goblin (attackRolls, attackDice, defenseRolls, defenseDice,
                      armor, HP, name, specialAbility)

    {
        this->attackRolls = attackRolls;
        this->attackDice = attackDice;
        this->defenseRolls = defenseRolls;
        this->defenseDice = defenseDice;
        this->armor = armor;
        this->HP = HP;
        this->specialAbility = specialAbility;
    }

   //this is the overridden function for goblin class. It adds a health regeneration
    //feature
    virtual int calculateHP (int attackSum, const int defenseSum, int remainingHealth)
    {
        //int remainingHealth;
        int regeneratedHealth;

        attackSum = attackSum - (defenseSum + this->armor);

        if (attackSum < 0)
        {
             attackSum = 0;
        }

        remainingHealth = remainingHealth - attackSum;

        cout <<"Regenerating health."<<endl;
        cout <<endl;

        regeneratedHealth = RNG (1 , 5);

        cout <<this->name<<" has regenerated "<<regeneratedHealth<<" health!"<<endl;
        cout <<endl;

        remainingHealth = remainingHealth +regeneratedHealth;

        if (remainingHealth >= this->HP)
        {
            remainingHealth = this->HP;
        }

        return remainingHealth;

    }

};

class Barbarian : public Creature
{
public:

     //default constructor
    Barbarian (int attackRolls = 3, int attackDice = 10, int defenseRolls = 2,
              int defenseDice = 10, int armor = 2, int HP = 12, string name ="Barbarian",
              string specialAbility = "Last Stand - after getting knocked out once, will come back with 3 HP."):
              Creature (attackRolls, attackDice, defenseRolls, defenseDice,
                      armor, HP, name, specialAbility)
    {
        this->attackRolls = attackRolls;
        this->attackDice = attackDice;
        this->defenseRolls = defenseRolls;
        this->defenseDice = defenseDice;
        this->armor = armor;
        this->HP = HP;
        this->specialAbility = specialAbility;
    }



    //this is the overridden function for goblin class. It adds a revive feature
    virtual int calculateHP (int attackSum, const int defenseSum, int remainingHealth)
    {

        attackSum = attackSum - (defenseSum + this->armor);

        if (attackSum < 0)
        {
             attackSum = 0;
        }

        remainingHealth = remainingHealth - attackSum;

        if (reviveSet == false && remainingHealth <= 0)
        {
            remainingHealth = 0;
            remainingHealth = remainingHealth+3;
            reviveSet = true;

            cout <<this->name<<" holds on to his life through sheer force of will! "<<
                 this->name<<" now has "<<remainingHealth<<" HP left."<<endl;
            cout <<endl;

        }

        return remainingHealth;

    }


};

class Zombie : public Barbarian
{
public:

    //default constructor
    Zombie (int attackRolls = 4, int attackDice = 8, int defenseRolls = 0,
              int defenseDice = 0, int armor = 2, int HP = 18, string name ="Zombie",
              string specialAbility = "Undead Charge - will only be knocked out after reaching -9 HP."):
              Barbarian (attackRolls, attackDice, defenseRolls, defenseDice,
                      armor, HP, name, specialAbility)
    {
        this->attackRolls = attackRolls;
        this->attackDice = attackDice;
        this->defenseRolls = defenseRolls;
        this->defenseDice = defenseDice;
        this->armor = armor;
        this->HP = HP;
        this->specialAbility = specialAbility;
    }

    //this is the overridden function for goblin class. It adds a revive feature
    virtual int calculateHP (int attackSum, const int defenseSum, int remainingHealth)
    {

        attackSum = attackSum - (defenseSum + this->armor);

        if (attackSum < 0)
        {
             attackSum = 0;
        }

        remainingHealth = remainingHealth - attackSum;

        if (remainingHealth > -9 && remainingHealth <= 0)
        {
            remainingHealth = 0;
            remainingHealth = remainingHealth+1;


            cout <<this->name<<" comes back to life! Kill it better next time! "<<
                 this->name<<" now has "<<remainingHealth<<" health left."<<endl;
            cout <<endl;

        }

        return remainingHealth;

    }

};

class Reptilian : public Creature
{
public:

    //default constructor
    Reptilian (int attackRolls = 3, int attackDice = 10, int defenseRolls = 1,
            int defenseDice = 6, int armor = 3, int HP = 15, string name = "Reptilian",
            string specialAbility = "Deadly Blows: has a 1 in 8 chance of striking critically and dealing double damage."):
            Creature (attackRolls, attackDice, defenseRolls, defenseDice,
                      armor, HP, name, specialAbility)

    {
        this->attackRolls = attackRolls;
        this->attackDice = attackDice;
        this->defenseRolls = defenseRolls;
        this->defenseDice = defenseDice;
        this->armor = armor;
        this->HP = HP;
        this->name = name;
        this->specialAbility = specialAbility;
    }

    //redefined function from Creature adds a critical strike ability
    virtual int getAttack ()
    {
        int attackSum = Creature::RNG(this->attackRolls, this->attackDice);

        criticalHit = Reptilian::RNG(1, 8);

        if (criticalHit == 1)
        {
            cout <<this->name<<" critically strikes! Damage doubled!"<<endl;
            cout <<endl;

            attackSum = attackSum*2;
        }

        return attackSum;
    }

    //ensures that the Creature's RNG function is used instead of it's own RNG function
    //the reason for this is because it's own function, used in criticalHit, does not
    //display the results of the dice rolls.
    int getDefense ()
    {
        int defenseSum = Creature::RNG (this->defenseRolls, this->defenseDice);

        return defenseSum;
    }

    //redefined function
    int RNG (const int diceRolls, const int diceSize);

protected:
    int criticalHit;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTION DECLARATIONS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This function fills each teams deque with pointers to the creatures that are selected by each player
//This is basically where each players line up of creatures is chosen and created.
void teamFiller (deque<Creature*> &team, string teamSet);

//This function ensures that bad input doesn't make it through the program
void stringConfirm(string &testedWord);

//This is where all the action happens. This function contains the loops that run until
//one creatures brings another creature to 0 HP and another loop that lasts until one
//team's lineup has been completely eliminated. This is where all the ADT manipulation occurs
void battle (deque<Creature*> &teamOne, deque<Creature*> &teamTwo, stack<Creature*> &standings);

//This is where the standings are output, the points for each team are calculated and a winning team
//is determined.
void getStandings (stack<Creature*> standings);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main ()
{
    deque<Creature*> teamOne;
    deque<Creature*> teamTwo;
    stack<Creature*> standings;
    string setTeamOne = "Team One";
    string setTeamTwo = "Team Two";
    string blank;



    cout <<"This a creature battle program. It is organized in a tournament style."<<endl;
    cout <<"Player one will draft a team of 4. Then player two will draft a team of 4."<<endl;
    cout <<"The first monsters drafted by each player will fight. The winner remains while"<<endl;
    cout <<"the loser is eliminated. When one team runs out of creatures, the tournament is finished."
         <<"The player with the higher rankings wins."<<endl;
    cout <<endl;

    cout <<"Player 1, choose your team."<<endl;
    cout <<endl;
    cout <<"Hit any key to display the stats of the creatures and"<<endl;
    cout <<"continue on to team draft mode."<<endl;
    getline (cin, blank);
    cout <<endl;
    teamFiller(teamOne, setTeamOne);

    cout <<"Player 2, choose your team."<<endl;
    cout <<endl;
    cout <<"Hit any key to display the stats of the creatures and"<<endl;
    cout <<"continue on to team draft mode."<<endl;
    getline (cin, blank);
    cout <<endl;
    teamFiller(teamTwo, setTeamTwo);

    battle(teamOne, teamTwo, standings);

    getStandings (standings);



    return 0;
}

int Creature::RNG (int diceRolls, int diceSize)
{
    string continueCheck;

    //vector used to save each roll value;
    vector<int> rollHolder(5);

    cout <<"# of dice rolls:"<<diceRolls<<endl;
    cout <<"# of dice size: "<<diceSize<<endl;
    cout <<endl;

    getline (cin, continueCheck);

    //seeds the random number generator
    srand (time(NULL));

    //Determines the amount of rolls
    for (int i = 1; i <= diceRolls; i++)
    {
        //determines the roll value
        rollHolder[i] = rand() % diceSize;
        cout <<"roll #"<<i<<": "<<rollHolder[i];
        getline (cin, continueCheck);
    }

    cout <<endl;
    cout <<endl;

    //returns the sum of all the rolls
    return rollHolder[1]+rollHolder[2]+rollHolder[3] + rollHolder[4];
}

//does not output the results of each roll
int Reptilian::RNG (int diceRolls, int diceSize)
{
    string continueCheck;

    //vector used to save each roll value;
    vector<int> rollHolder(5);

    //seeds the random number generator
    srand (time(NULL));

    //Determines the amount of rolls
    for (int i = 1; i <= diceRolls; i++)
    {
        //determines the roll value
        rollHolder[i] = rand() % diceSize;
    }

    cout <<endl;
    cout <<endl;

    //returns the sum of all the rolls
    return rollHolder[1]+rollHolder[2]+rollHolder[3] + rollHolder[4];
}

void teamFiller (deque<Creature*> &team, string teamSet)
{
    string creatureChoice;
    string teamConfirm = "no";
    Goblin goblin;
    Ogre ogre;
    Barbarian barbarian;
    Zombie zombie;
    Reptilian reptilian;


    //prints all the stats for each creature
    goblin.printAll();
    cout <<"***********************************************************"<<endl;
    cout <<endl;
    ogre.printAll();
    cout <<"***********************************************************"<<endl;
    cout <<endl;
    barbarian.printAll();
    cout <<"***********************************************************"<<endl;
    cout <<endl;
    zombie.printAll();
    cout <<"***********************************************************"<<endl;
    cout <<endl;
    reptilian.printAll();
    cout <<"***********************************************************"<<endl;
    cout <<endl;
    cout <<endl;

    //this loop allows the user to verify that they chose the team they intended
    while (teamConfirm == "no"||teamConfirm == "No"||teamConfirm == "NO"||teamConfirm == "n"||teamConfirm == "N")
    {

        cout <<"Enter 1 for Goblin."<<endl;
        cout <<"Enter 2 for Ogre."<<endl;
        cout <<"Enter 3 for Barbarian."<<endl;
        cout <<"Enter 4 for Zombie."<<endl;
        cout <<"Enter 5 for Reptilian."<<endl;
        cout <<endl;


        for (int i = 1; i <= MAXTEAMSIZE; i++)
        {

            cout <<"Enter creature choice #"<<i<<":"<<endl;
            getline (cin, creatureChoice);
            cout <<endl;
            stringConfirm(creatureChoice);


            //this if statements fill the deque with pointers to a certain child class of creature.
            if(creatureChoice == "1")
            {
                Goblin* g_ptr = new Goblin;
                team.push_back(g_ptr);
            }

            if(creatureChoice == "2")
            {
                Ogre* o_ptr= new Ogre;
                team.push_back(o_ptr);
            }

            if(creatureChoice == "3")
            {
                Barbarian* b_ptr = new Barbarian;
                team.push_back(b_ptr);
            }


            if(creatureChoice == "4")
            {
                Zombie* z_ptr = new Zombie;
                team.push_back (z_ptr);
            }

            if(creatureChoice == "5")
            {
                Reptilian* r_ptr = new Reptilian;
                team.push_back(r_ptr);
            }
        }

        //this loop locks the creatures team variable to either team one or two. This is used
        //to calculate points and two clear up confusion during the battle function.
        for (int i = 0; i < team.size(); i++)
        {
            team.at(i)->setTeam(teamSet);
        }

        //outputs the user's choices for their team
        cout<<"You chose:"<<endl;
        cout<<endl;
        for (int i = 0; i < team.size(); i++)
        {
            cout<<team.at(i)->getName()<<endl;
            cout<<endl;

        }
        cout <<endl;


        cout <<"Are those the combatants you wanted to choose? Y/N"<<endl;
        cout <<endl;
        //cin.ignore(1000,'\n');
        getline (cin,teamConfirm);
        if (teamConfirm == "no"||teamConfirm == "No"||teamConfirm == "NO"||
            teamConfirm == "n"||teamConfirm == "N")
        {
            team.clear();
        }
        cout <<endl;
        cout <<endl;
        cout <<endl;
    }
}

void battle (deque<Creature*> &teamOne, deque<Creature*> &teamTwo, stack<Creature*> &standings)
{
        string blank;
        int roundCounter = 1;
        int fightCounter = 1;
        int attackSum;
        int defenseSum;
        int playerOneHP;
        int playerTwoHP;
        int i = 0;
        int j = 0;
        Creature* temp;



        //lasts until one team runs out of combatants
        while (teamOne.size()> 0 && teamTwo.size()> 0)
        {
            cout <<"*******************"<<endl;
            cout <<"*      FIGHT "<<fightCounter<<"    *"<<endl;
            cout <<"*******************"<<endl;
            cout <<endl;
            cout <<endl;
            fightCounter++;

            //sets the two combatants health to the proper positions
            playerOneHP = teamOne.at(0)->getHPs();
            playerTwoHP = teamTwo.at(0)->getHPs();

            //this is used to make sure that the barbarians revive mechanic is functioning correctly
            teamOne.at(0)->setReviveSet(false);
            teamTwo.at(0)->setReviveSet(false);

            //lasts until one creature gets knocked out (reaches 0 or below HP)
            while (playerOneHP > 0 && playerTwoHP > 0)
            {
                cout <<"*******************"<<endl;
                cout <<"*      ROUND "<<roundCounter<<"    *"<<endl;
                cout <<"*******************"<<endl;
                cout <<endl;
                cout <<endl;
                roundCounter++;

                //player one attacks, player two defends
                if (playerOneHP > 0 && playerTwoHP > 0)
                {
                    cout <<teamOne.at(i)->getTeam()<<"'s "<<teamOne.at(i)->getName()<<" is attacking!"<<endl;
                    cout <<endl;
                    attackSum = teamOne.at(i)->getAttack();

                    cout <<teamOne.at(i)->getTeam()<<"'s "<<teamOne.at(i)->getName()<<"'s Attack Sum is "<<attackSum<<endl;
                    cout <<endl;

                    cout <<teamTwo.at(i)->getTeam()<<"'s "<<teamTwo.at(i)->getName()<<" is defending!"<<endl;
                    cout <<endl;
                    defenseSum = teamTwo.at(i)->getDefense();

                    cout <<teamTwo.at(i)->getTeam()<<"'s "<<teamTwo.at(i)->getName()<<"'s Defense Sum is "<<defenseSum<<endl;
                    cout <<endl;

                    playerTwoHP = teamTwo.at(i)->calculateHP(attackSum, defenseSum, playerTwoHP);
                    cout <<teamTwo.at(i)->getTeam()<<"'s "<<teamTwo.at(i)->getName()<<" has "<<playerTwoHP<<" remaining health."<<endl;
                    cout <<endl;
                }

                //player two attacks, player one defends
                if (playerOneHP > 0 && playerTwoHP > 0)
                {
                    cout <<teamTwo.at(i)->getTeam()<<"'s "<<teamTwo.at(i)->getName()<<" is attacking!"<<endl;
                    cout <<endl;
                    attackSum = teamTwo.at(i)->getAttack();

                    cout <<teamTwo.at(i)->getTeam()<<"'s "<<teamTwo.at(i)->getName()<<"'s Attack Sum is "<<attackSum<<endl;
                    cout <<endl;

                    cout <<teamOne.at(i)->getTeam()<<"'s "<<teamOne.at(i)->getName()<<" is defending!"<<endl;
                    cout <<endl;
                    defenseSum = teamOne.at(i)->getDefense();

                    cout <<teamOne.at(i)->getTeam()<<"'s "<<teamOne.at(i)->getName()<<"'s Defense Sum is "<<defenseSum<<endl;
                    cout <<endl;

                    playerOneHP = teamOne.at(i)->calculateHP(attackSum, defenseSum, playerOneHP);
                    cout <<teamOne.at(i)->getTeam()<<"'s "<<teamOne.at(i)->getName()<<" has "<<playerOneHP<<" remaining health."<<endl;
                    cout <<endl;

                }

                //this is where the ADT manipulation occurs
                if (playerTwoHP <= 0)
                {
                    cout <<teamTwo.at(i)->getTeam()<<"'s "<<teamTwo.at(i)->getName()<<" has been defeated! "<<teamOne.at(i)->getTeam()<<"s "
                         <<teamOne.at(i)->getName()<<" is the winner!"<<endl;

                    cout <<endl;

                    //puts the losing creature into the standings stack
                    temp =  teamTwo.at(i);
                    standings.push(temp);
                    teamTwo.erase(teamTwo.begin());

                    //adds a win to the winning creature then moves it to the back of the deque
                    teamOne.at(i)->setNumberOfWins(teamOne.at(i)->getNumberOfWins()+1);
                    temp = teamOne.at(i);
                    teamOne.erase(teamOne.begin());
                    teamOne.push_back(temp);


                }
                //this is where the ADT manipulation occurs
                else if (playerOneHP <= 0)
                {
                    cout <<teamOne.at(i)->getTeam()<<"'s "<<teamOne.at(i)->getName()<<" has been defeated! "<<teamTwo.at(i)->getTeam()<<"'s "
                         <<teamTwo.at(i)->getName()<<" is the winner!"<<endl;
                    cout <<endl;

                    //puts the losing creature into the standings stack
                    temp =  teamOne.at(i);
                    standings.push(temp);
                    teamOne.erase(teamOne.begin());

                    //adds a win to the winning creature then moves it to the back of the deque
                    teamTwo.at(i)->setNumberOfWins(teamTwo.at(i)->getNumberOfWins()+1);
                    temp = teamTwo.at(i);
                    teamTwo.erase(teamTwo.begin());
                    teamTwo.push_back(temp);
                }
            }

            if (teamOne.size()< 1)
            {
                cout <<"Team One has run out of combatants. The standings will now be posted."<<endl;
                cout <<endl;

                //moves the remaining creatures on the winning team to the standings stack
                for (int i = 0; i < teamTwo.size(); i++)
                {
                    temp =  teamTwo.at(i);
                    standings.push(temp);
                }
            }

            else if (teamTwo.size()< 1)
            {
                cout <<"Team Two has run out of combatants. The standings will now be posted."<<endl;
                cout <<endl;

                //moves the remaining creatures on the winning team to the standings stack
                for (int i = 0; i < teamOne.size(); i++)
                {
                    temp =  teamOne.at(i);
                    standings.push(temp);
                }
            }
        }
}

void stringConfirm(string &testedWord)
{

    string testedWordCopy = testedWord;
    bool validWordOne = false;
    bool validWordTwo = false;



    //loops while the input entered is not valid
    while (validWordOne == false || validWordTwo == false)
    {


        //makes sure that if nothing is entered at
        //all, it will be considered invalid input
        if (testedWord.empty())
        {
            validWordOne = false;
        }
        else
        {
            validWordOne = true;
        }

        //makes sure only 1, 2, 3, or 4 can be entered and accepted
        if (testedWord == "1" || testedWord == "2"
            ||testedWord == "3" || testedWord == "4"||
            testedWord == "5")
        {
            validWordTwo = true;
        }
        else
        {
            validWordTwo = false;
        }

        //prompts the user for new input if the word is not valid
        if (!validWordOne || !validWordTwo)
        {
            cout <<"Input invalid. No blank entry. Enter a number between 1 and 5."<< endl;
            getline (cin, testedWord);
            cout << endl;
            testedWordCopy = testedWord;

            validWordOne = false;
            validWordTwo = false;
        }
    }

}

void getStandings (stack<Creature*> standings)
{
    int teamOneSum = 0;
    int teamTwoSum = 0;
    int st_num = 1;


    cout <<endl;
    cout <<endl;
    cout <<endl;
    cout <<"The standings are: "<<endl;
    cout <<endl;

    //outputs the standings
    while (!standings.empty())
    {
        cout <<"#"<<st_num<<" is "<<standings.top()->getTeam()<<"'s "<<standings.top()->getName()<<endl;
        cout <<"Wins: "<<standings.top()->getNumberOfWins()<<endl;

        //the portion below gives out the points to each team
        if (standings.top()->getTeam() == "Team One")
        {
            teamOneSum = teamOneSum + standings.top()->getNumberOfWins();

            if (st_num == 8 || st_num == 7 || st_num == 6)
            {
                teamOneSum = teamOneSum + 1;
            }
            else if (st_num == 5 || st_num == 4)
            {
                teamOneSum = teamOneSum + 2;
            }
            else if (st_num == 3)
            {
                teamOneSum = teamOneSum + 3;
            }
            else if (st_num == 2)
            {
                teamOneSum = teamOneSum + 4;
            }
            else if (st_num == 1)
            {
                teamOneSum = teamOneSum + 5;
            }

        }

        else if (standings.top()->getTeam() == "Team Two")
        {
            teamTwoSum = teamTwoSum + standings.top()->getNumberOfWins();

            if (st_num == 8 || st_num == 7 || st_num == 6)
            {
                teamTwoSum = teamTwoSum + 1;
            }
            else if (st_num == 5 || st_num == 4)
            {
                teamTwoSum = teamTwoSum + 2;
            }
            else if (st_num == 3)
            {
                teamTwoSum = teamTwoSum + 3;
            }
            else if (st_num == 2)
            {
                teamTwoSum = teamTwoSum + 4;
            }
            else if (st_num == 1)
            {
                teamTwoSum = teamTwoSum + 5;
            }

        }
        standings.pop();
        cout <<endl;
        st_num++;
    }

    cout <<"The standings will now be calculated. Numbers 8, 7 and 6 will receive"<<endl;
    cout <<"1 point for their team. Numbers 4 and 5 will receive 2 points for"<<endl;
    cout <<"their team. Number 3 receives 3 points, number 2 receives 4 points and"<<endl;
    cout <<"number 1 receives 5 points. Each contestant will also receive points"<<endl;
    cout <<"for each win they got. The team with more points wins."<<endl;
    cout <<endl;
    cout <<endl;

    if (teamOneSum > teamTwoSum)
    {
        cout <<"Team One has accrued "<<teamOneSum<<" points. Team Two has accrued "<<teamTwoSum<<" points."<<endl;
        cout <<"Team One is the winner!"<<endl;
        cout <<endl;
    }
    else if (teamTwoSum > teamOneSum)
    {
        cout <<"Team One has accrued "<<teamOneSum<<" points. Team Two has accrued "<<teamTwoSum<<" points."<<endl;
        cout <<"Team Two is the winner!"<<endl;
        cout <<endl;
    }
    else if (teamTwoSum == teamOneSum)
    {
        cout <<"Team One has accrued "<<teamOneSum<<" points. Team Two has accrued "<<teamTwoSum<<" points."<<endl;
        cout <<"We have a tie!"<<endl;
        cout <<endl;
    }
}
