#include <string>
#include <map>

class Team
{
private:
    std::string name;

    std::map<std::string, int> current_wins;
    std::map<std::string, int> current_loses;
    std::map<std::string, int> past_wins;

    std::map<std::string, double> betting_odd;
    std::map<std::string, double> opposite_betting_odd;

    std::map<std::string, int> num_of_goals_against; // map<name of opposite, goals against>

    
public:
    Team(std::string name) : name(name) {};
};