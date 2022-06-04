#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>

#define GRAVITY 9.81
// units of gravity are m/s^2

template <typename T>
T potentialEnergy(T height, T mass){
    // remember height has to be in meters and mass has to be in kg
    return (mass*GRAVITY*height);
}

// function declarations
void display_menu();
void display_previous_calculations();
void output_to_file();
double verticalToSquat(double height, double user_weight);
double squatToVertical(double squat_weight, double user_weight);
double poundToKg(double pound);
double kgToPound(double kg);
double inchesToMeters(double inches);
double metersToInches(double meters);
double squat(double PE, double height);

// global variables
std::vector<std::vector<double>> record_of_calculations;

int main(){
    
    std::cout << "This small program is an approximation to how much you need squat in order to achieve a certain standing vertical jump\n" << std::endl;
    std::cout << "The only equation used for this program is the potential energy to reach a certain vertical = potential energy needed to squat a certain weight. So the equation looks like: m1*g*h1 = m2*g*h2 or just m1*h1 = m2*h2 where:" << std::endl;
    std::cout << std::endl;
    std::cout << "m1 = mass of yourself - this is the mass that you're trying to bring to a certain height" << std::endl;
    std::cout << "h1 = vertical jump distance" << std::endl;
    std::cout << "m2 = squat weight" << std::endl;
    std::cout << "h2 = distance travelled of squat " << std::endl;
    std::cout << std::endl;
    
    std::cout << "Please read the following assumptions / user info needed: \n" << std::endl;
    std::cout << "1. User must enter in mass in lbs. The program will automatically convert the lbs to kg." << std::endl;
    std::cout << "2. User must enter in distance in inches. The program will automatically convert the inches to meters" << std::endl;
    std::cout << "3. The first assumption here is that the kinetic energy (KE) for each situation is the same so only PE effects are evaluted. " << std::endl;
    std::cout << "4. The second assumption is that the weight will travel around 17 inches when you squat up and down. That's about the length of your upper leg.\n" << std::endl; 
    
    std::cout << "If you agree with the user input requirements and assumptions, please type yes to continue to program menu." << std::endl;
    std::string user_agreement;
    std::getline(std::cin, user_agreement);
    
    if (user_agreement != "yes") {
        return 0;
    }
    
    std::cout << std::endl;
    display_menu();
    int choice;
    
    std::cin >> choice;
    std::cout << std::endl;
    
//    std::vector<std::vector<double>> record_of_calculations;
    while (choice !=5){
        if (choice==1){
            // enter in function for vertical jump based on input of squat weight
            double user_squat_weight;
            double user_weight;
            
            std::cout << "Please enter in how much you squat in lbs: ";
            std::cin >> user_squat_weight;
            
            std::cout << "Please enter in how much you weigh in lbs: ";
            std::cin >> user_weight;
            
            double desired_vertical = squatToVertical(user_squat_weight,user_weight);
            
            std::cout << std::endl;
            std::cout << "If you squat " << user_squat_weight << " lbs, you can have a standing vertical jump of " << desired_vertical << " inches.\n" << std::endl;
            // store the calculation into record of calculations vector 
            
            record_of_calculations.push_back({1,user_squat_weight,desired_vertical});
            
        } else if (choice == 2) { // choice==2
            // enter in function for squat weight based on vertical jump
            double user_vertical;
            double user_weight;
            
            std::cout << "Please enter in how much you can jump from a standing/neutral position: ";
            std::cin >> user_vertical;
            
            std::cout << "Please enter in how much you weigh in lbs: ";
            std::cin >> user_weight; 
            
            double desired_squat = verticalToSquat(user_vertical,user_weight);
            
            std::cout << std::endl;
            std::cout << "If you can or want to jump " << user_vertical << " inches, you have to squat at least " << desired_squat << " lbs.\n" << std::endl;          

            record_of_calculations.push_back({2,user_vertical,desired_squat});
            
        } else if (choice == 3){
            display_previous_calculations();
        } else if (choice ==4){
            output_to_file();
        }
             
        display_menu();
        std::cin >> choice;
        std::cout << std::endl;
    }
    
    
    std::cout << "Thank you for using my program. Goodbye!" << std::endl;
    
    return 0;
}

void display_menu(){
    std::cout << "Please select from the following: " << std::endl;
    std::cout << "1. Determine vertical jump height required from squat weight" << std::endl;
    std::cout << "2. Determine squat weight required for vertical jump height" << std::endl;
    std::cout << "3. Print out previous calculations" << std::endl;
    std::cout << "4. Send calculations out to text file" << std::endl;
    std::cout << "5. QUIT" << std::endl;
}

void display_previous_calculations(){
    std::cout << std::setprecision(0) << std::fixed;
    std::cout << "ID" << "                     " << "Calculation Description" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------" << std::endl;
    for (int i=0;i<record_of_calculations.size();i++){
        if (record_of_calculations[i][0]==1){
            std::cout << i+1 << "                      " << "If you squat " << record_of_calculations[i][1] << " lbs, you can have a standing vertical jump of " <<  record_of_calculations[i][2] << " inches.\n" << std::endl;
        } else if (record_of_calculations[i][0]==2){
            std::cout << i+1 << "                      " << "If you can or want to jump " << record_of_calculations[i][1] << " inches, you have to squat at least " << record_of_calculations[i][2] << " lbs.\n" << std::endl;       
        }
    }
}

void output_to_file(){
    std::cout << "Outputting previous calculations to external text file..." << std::endl;
    std::ofstream outfile ("verticalJump_Calculations.txt");

    outfile << std::setprecision(0) << std::fixed;
    outfile << "ID" << "                     " << "Calculation Description" << std::endl;
    outfile << "------------------------------------------------------------------------------------------------------------------" << std::endl;
    for (int i=0;i<record_of_calculations.size();i++){
        if (record_of_calculations[i][0]==1){
            outfile << i+1 << "                      " << "If you squat " << record_of_calculations[i][1] << " lbs, you can have a standing vertical jump of " <<  record_of_calculations[i][2] << " inches.\n" << std::endl;
        } else if (record_of_calculations[i][0]==2){
            outfile << i+1 << "                      " << "If you can or want to jump " << record_of_calculations[i][1] << " inches, you have to squat at least " << record_of_calculations[i][2] << " lbs.\n" << std::endl;       
        }
    }
    std::cout << std::endl;
}

double squatToVertical(double squat_weight, double user_weight){
    // determine potential energy required of squat based on weight
    double distanceConverted = inchesToMeters(17);
    double weightConverted = poundToKg(squat_weight);
    double userWeightConverted = poundToKg(user_weight);
    double PE_from_squat = potentialEnergy(distanceConverted,weightConverted);
    
    double vertical = PE_from_squat / (GRAVITY*userWeightConverted);
    return metersToInches(vertical);
}

double verticalToSquat(double height, double user_weight){
    // determine potential energy required of squat based on weight
    double distanceConverted = inchesToMeters(17);
    double verticalConverted = inchesToMeters(height);
    double userWeightConverted = poundToKg(user_weight);
    double PE_from_vertical = potentialEnergy(verticalConverted,userWeightConverted);
    
    double squatWeight =  PE_from_vertical / (GRAVITY*distanceConverted);
    
    return kgToPound(squatWeight);
}

double poundToKg(double pound){
    return pound*0.453592;
}

double kgToPound(double kg){
    return kg*2.20462;
}

double inchesToMeters(double inches){
    return inches*0.0254;
}

double metersToInches(double meters){
    return meters*39.3701;
}

// math logic:
// to jump 30" from the ground...and i'm 160lb...which converted to kg is about 72.5748kg
// 30 inches to meters is 0.762 meters
// E = mgh; 
// 1lb = 0.453592 kg
// 1 inch is 0.0254 m

// m1gh1 = m2gh2
// h1 (vertical height)  = (PE_from_squat) / m1*g