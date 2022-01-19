#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include "thirdpartylibrary/rapidcsv.h"
using namespace std;

class CovidData{  //My relation class called "Rel".
	private:
        vector<struct CountryInfo> totalVector= {}; //Creating a vector for holding elements.
		vector<string> countries = { }; 	    //Creating  empty vector for holding elements.
        vector<string> dates     = { };     	//Creating  empty vector for holding elements.
        vector<string> totalCases= { }; 	    //Creating  empty vector for holding elements.
        vector<string> totalDeaths= { }; 	    //Creating  empty vector for holding elements.
        vector<string> reproductionRates={};    //Creating  empty vector for holding elements.
        vector<string> icu_patients = {};       //Creating  empty vector for holding elements.
        vector<string> hosp_patients= {};       //Creating  empty vector for holding elements.
        vector<string> weekly_icu_admissions= {};     //Creating  vector for holding elements.
        vector<string> weekly_hosp_admissions= {};    //Creating  vector for holding elements.
        vector<string> new_tests = {};          //Creating  empty vector for holding elements.
        vector<string> positive_rate = {};      //Creating  empty vector for holding elements.
        vector<string> tests_per_case = {};     //Creating  empty vector for holding elements.
        vector<string> total_tests = {};             //Creating a vector for holding elements.
        vector<string> people_vaccinated = {};       //Creating a vector for holding elements.
        vector<string> people_fully_vaccinated = {}; //Creating a vector for holding elements.
        vector<string> total_vaccinations = {};      //Creating a vector for holding elements.
        vector<string> human_development_index = {}; //Creating a vector for holding elements.
        vector<string> life_expectancy = {};         //Creating a vector for holding elements.
        vector<string> hospital_beds_per_thousand = {};//Creating vector for holding elements.
        vector<string> handwashing_facilities = {};  //Creating a vector for holding elements.
        vector<string> male_smokers = {};            //Creating a vector for holding elements.
        vector<string> female_smokers = {};          //Creating a vector for holding elements.
        vector<string> diabetes_prevalence = {};     //Creating a vector for holding elements.
        vector<string> cardiovasc_death_rate = {};   //Creating a vector for holding elements.
        vector<string> extreme_poverty = {};         //Creating a vector for holding elements.
        vector<string> gdp_per_capita = {};          //Creating a vector for holding elements.
        vector<string> aged_70_older = {};           //Creating a vector for holding elements.
        vector<string> aged_65_older = {};           //Creating a vector for holding elements.
        vector<string> median_age = {};              //Creating a vector for holding elements.
        vector<string> population = {};      //Creating a vector for holding elements.
        //Creating empty vectors to hold data for min,max and average values of all countries.	    
        vector<double> min5, max5, min12, max12, min13, max13; 
        vector<double> mean5, mean6, mean7, mean8, mean9, mean10, mean12, mean13;
        vector<int> min6, max6, min7, max7, min8, max8, min9, max9;
        vector<long long int> min10, max10;
        vector<double> variationValue5, variationValue6, variationValue7, variationValue8;
        vector<double> variationValue9, variationValue10, variationValue12, variationValue13;
        static ofstream filestream;


	public:
		void getInfoFromFile(); //Reads the csv document with 3rd library csv reader class.
        void writeInfoToFile(); //Writes all the information to file.
        void question5(rapidcsv::Document doc); //Solution of question.
        void question6(rapidcsv::Document doc); //Solution of question.
        void question7(rapidcsv::Document doc); //Solution of question.
        void question8(rapidcsv::Document doc); //Solution of question.
        void question9(rapidcsv::Document doc); //Solution of question.
        void question10(rapidcsv::Document doc); //Solution of question.
        void question11(rapidcsv::Document doc); //Solution of question.
        void question12(rapidcsv::Document doc); //Solution of question.
        void question13(rapidcsv::Document doc); //Solution of question.
        void question14(rapidcsv::Document doc); //Solution of question.
        void question15(rapidcsv::Document doc); //Solution of question.
        void question16(rapidcsv::Document doc); //Solution of question.
        void question17(rapidcsv::Document doc); //Solution of question.
        void question18();                       //Solution of question.
};

class Date{
    private:
        int year, month, day;
    public:
        void setDay (int     day ){ this->day   = day;   }
        void setYear(int    year ){ this->year  = year;  }
        void setMonth (int month ){ this->month = month; }
        int  getDay()  { return day;   }
        int  getMonth(){ return month; }
        int  getYear() { return year;  }
        friend bool operator< ( Date const& a, Date const& b);
};

struct CountryInfo{
    string country;
    int cases;
    int deaths;
    double reproductionRate;
    int icuPatients;
    int hospPatients;
    int weeklyIcu;
    int weeklyHospAdmis;
    int newTestPerDay;
    int testConducted;
    double positiveRate;
    double testPerCase;
    int vaccinated;
    int fullVaccinated;
    int vaccinations;
    int howManyElementsFromThatCountry;
    int totalTests;
    int population;
    double medianAge;
    double aged65Older;
    double aged70Older;
    double gdpPerCapita;
    double extremePoverty;
    double cardiovascDeathRate;
    double diabetesPrevalence;
    double femaleSmokers;
    double maleSmokers;
    double handwashingFacilities;
    double hospitalBedsPerThousand;
    double lifeExpectancy;
    double humanDevelopmentIndex;
};


bool operator< (Date const& a, Date const& b){ //Operator overloading for < comparing.
    if(a.year < b.year){
        return true;
    }
    else if(a.year > b.year){
        return false;
    }
    else{ //a.year = b.year
        if(a.month < b.month)   return  true;
        if(a.month > b.month)   return false;
        if(a.month == b.month){
            if(a.day <= b.day) return true;
            else return false;
        }
    }
    return false;
}

ofstream CovidData::filestream;

int main(){
    CovidData data;
    data.getInfoFromFile();
}

void CovidData::getInfoFromFile(){
    filestream.open( "output.txt",ios::out);
    if( !filestream.is_open() ){
        cout << "Error while writing to file.\n";
        return;
    }

    rapidcsv::Document doc("owid-covid-data.csv");
    cout << "Writing to file please wait.\n";

    //Question1- How many countries the dataset has?
    CovidData::countries = doc.GetColumn<string>("location");
    int countryCounter = 0;
    for(size_t i=0; i<countries.size(); i++){
        if(countries[i+1] != countries[i] )
            countryCounter++;
    }
    filestream << "There are " << countryCounter << " countries.\n";

    //Question2- When is the earliest date data are taken for a country? Which country is it?
    CovidData::dates = doc.GetColumn<string>("date");
    int day, month, year;
    vector<Date> date = { };
    Date earliestDate;
    string earliestCountry;

    for(size_t i=0; i<dates.size(); i++){
        stringstream ss( dates[i] );
        date.push_back( Date() );
        ss >> year; date[i].setYear(year);
        if(ss.peek() == '-'){ ss.ignore(); }
        ss >> month;  date[i].setMonth(month);
        if(ss.peek() == '-'){ ss.ignore(); }
        ss >> day;  date[i].setDay(day);
        if(i==0) earliestDate = date[0];

        if(date[i] < earliestDate){
            earliestDate = date[i];
            earliestCountry = countries[i];
        }

    }
    filestream <<"First data is from " << earliestCountry << " " << earliestDate.getYear() << " " <<earliestDate.getMonth() << " " << earliestDate.getDay() << endl;

    //Question3- How many cases are confirmed for each country so far? Print pairwise results of country and total cases.
    //Question4. How many deaths are confirmed for each country so far? Print pairwise results of country and total deaths.
    CovidData::totalCases = doc.GetColumn<string>("total_cases");
    CovidData::totalDeaths = doc.GetColumn<string>("total_deaths");
    int countryNo = 0;

    for(size_t i=0; i<dates.size(); i++){
        if(countries[i+1] != countries[i]){
            totalVector.push_back ( CountryInfo() );
            if( totalCases[i] == "" ) totalCases[i] = "0"; //Because of some days are empty it gives error if I don't convert to integer 0.
            if(totalDeaths[i] == "" ) totalDeaths[i] = "0"; //Because of some days are empty it gives error if I don't convert to integer 0.
            totalVector[countryNo].country = countries[i];
            totalVector[countryNo].cases += stoi( totalCases[i] ); //data in the last day
            totalVector[countryNo].deaths += stoi( totalDeaths[i] );
            filestream << "Country: " << totalVector[countryNo].country << " Total Cases: " << totalVector[countryNo].cases<< " Total Deaths: " << totalVector[countryNo].deaths << endl; 
            countryNo++;
        }
    }
    
    //Question5. What are the average, minimum, maximum and variation values of the reproduction rates for each country?
    question5(doc);
    //Question6What are the average, minimum, maximum and variation values of the icu patients (intensive care unit patients) for each country?
    question6(doc);
    //Question7. What are the average, minimum, maximum and variation values of the hosp patients (hospital patients) for each country?
    question7(doc);
    //Question8. What are the average, minimum, maximum and variation values of the weekly icu (intensive care unit) admissions for each country?
    question8(doc);
    //Question9. What are the average, minimum, maximum and variation values of the weekly hospital admissions for each country?
    question9(doc);
    //Question10. What are the average, minimum, maximum and variation values of new tests per day for each country?
    question10(doc);
    //Question11. How many tests are conducted in total for each country so far?
    question11(doc);
    //Question12. What are the average, minimum, maximum and variation values of the positive rates of the tests for each country?
    question12(doc);
    //Question13. What are the average, minimum, maximum and variation values of the tests per case for each country?
    question13(doc);
    // 14. How many people are vaccinated by at least one dose in each country?
    question14(doc);
    // 15. How many people are vaccinated fully in each country?
    question15(doc);
    // 16. How many vaccinations are administered in each country so far?
    question16(doc);
    // List information about many things.
    question17(doc);
    // Summarize all the results 
    question18();

}

void CovidData::question5(rapidcsv::Document doc){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(2); //Like %.2f c++ version
    CovidData::reproductionRates = doc.GetColumn<string>("reproduction_rate");

    int countryNo = 0;
    totalVector[countryNo].howManyElementsFromThatCountry = 0; //We will divide sum to it to find average value.
    totalVector[countryNo].reproductionRate = 0.0;  //Total value for all countries. When we divide it to howManyElementsFromThatCountry, we will find average.
    min5.push_back( 10000 ), max5.push_back( -10000 );
    for(size_t i=0; i<dates.size(); i++){
        if(reproductionRates[i] == ""){ //If there is no data about it 
            if(countries[i+1] != countries[i]){ //Check if country is changing
                min5.push_back( 10000 ), max5.push_back( -10000 );  //If at last, the values are like that it means no data collected about it.
                mean5.push_back( totalVector[countryNo].reproductionRate / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) ); //Adding average value to vector
                countryNo++;
                totalVector[countryNo].howManyElementsFromThatCountry = 0;
                totalVector[countryNo].reproductionRate = 0.0;
            }
            continue;
        }
        if( stod( reproductionRates[i] ) < min5[countryNo] )    min5[countryNo] = stod( reproductionRates[i] );
        if( stod( reproductionRates[i] ) > max5[countryNo] )    max5[countryNo] = stod( reproductionRates[i] );
        totalVector[countryNo].reproductionRate += stod( reproductionRates[i] );  //Total of reproductionRates to calculate average.
        totalVector[countryNo].howManyElementsFromThatCountry++;
    }
    filestream << "\nQUESTION5- REPRODUCTION RATES\nCOUNTRY MINIMUM MAXIMUM AVERAGE VARIATION" << endl;
    //FINDING VARIATION
    variationValue5.resize(dates.size());
    countryNo=0;
    double sum=0;
    for(size_t i=0; i<dates.size(); i++){
        if(reproductionRates[i] != "")
            sum += pow( stod(reproductionRates[i])-mean5[countryNo], 2);
        if(countries[i+1] != countries[i]){
            variationValue5[countryNo] = sum/(totalVector[countryNo].howManyElementsFromThatCountry-1.0);
            if(min5[countryNo] == 10000) //Then also there is no average or variation data.
                filestream << totalVector[countryNo].country << " NO INFO NO INFO NO INFO NO INFO" << endl;
            else    
                filestream << totalVector[countryNo].country << " " << min5[countryNo] << " " << max5[countryNo] << " " << mean5[countryNo] << " " << variationValue5[countryNo] << endl;
            sum = 0;    
            countryNo++; 
        }
    }

}

void CovidData::question6(rapidcsv::Document doc){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(2); //Like %.2f c++ version
    CovidData::icu_patients = doc.GetColumn<string>("icu_patients");
    
    int countryNo = 0;
    totalVector[countryNo].howManyElementsFromThatCountry = 0;  //We will divide sum to it to find average value.
    totalVector[countryNo].icuPatients = 0;   //Total value for all countries. When we divide it to howManyElementsFromThatCountry, we will find average.
    min6.push_back( 10000 ), max6.push_back( -10000 );
    for(size_t i=0; i<dates.size(); i++){
        if(icu_patients[i] == ""){      //If there is no data about it 
            if(countries[i+1] != countries[i]){ //Check if country is changing
                min6.push_back( 10000 ), max6.push_back( -10000 );    //If at last, the values are like that it mean6s no data collected about it.
                mean6.push_back( totalVector[countryNo].icuPatients / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) );   //Adding average value to vector
                countryNo++;
                totalVector[countryNo].howManyElementsFromThatCountry = 0;
                totalVector[countryNo].icuPatients = 0.0;
            }
            continue;
        }
        if( stoi( icu_patients[i] ) < min6[countryNo] )    min6[countryNo] = stoi( icu_patients[i] );
        if( stoi( icu_patients[i] ) > max6[countryNo] )    max6[countryNo] = stoi( icu_patients[i] );
        totalVector[countryNo].icuPatients += stod( icu_patients[i] );  //Total of reproductionRate to calculate average.
        totalVector[countryNo].howManyElementsFromThatCountry++;
    }
    
    //FINDING VARIATION
    variationValue6.resize(dates.size());
    countryNo=0;
    filestream << "\nQUESTION6- ICU_PATIENTS\nCOUNTRY MINIMUM MAXIMUM AVERAGE VARIATION" << endl;
    double sum=0;
    for(size_t i=0; i<dates.size(); i++){
        if(icu_patients[i] != "")
            sum += pow( stod(icu_patients[i])-mean6[countryNo], 2);
        if(countries[i+1] != countries[i]){
            variationValue6[countryNo] = sum/(totalVector[countryNo].howManyElementsFromThatCountry-1.0);
            if(min6[countryNo] == 10000) //Then also there is no average or variation data.
                filestream << totalVector[countryNo].country << " NO INFO NO INFO NO INFO NO INFO" << endl;
            else    
                filestream << totalVector[countryNo].country << " " << min6[countryNo] << " " << max6[countryNo] << " " << mean6[countryNo] << " " << variationValue6[countryNo] << endl;
            sum = 0;    
            countryNo++; 
        }
    }

}

void CovidData::question7(rapidcsv::Document doc){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(2); //Like %.2f c++ version
    CovidData::hosp_patients = doc.GetColumn<string>("hosp_patients");

    int countryNo = 0;
    totalVector[countryNo].howManyElementsFromThatCountry = 0;  //We will divide sum to it to find average value.
    totalVector[countryNo].hospPatients = 0;   //Total value for all countries. When we divide it to howManyElementsFromThatCountry, we will find average.
    min7.push_back( 10000 ), max7.push_back( -10000 );
    for(size_t i=0; i<dates.size(); i++){
        if(hosp_patients[i] == ""){      //If there is no data about it 
            if(countries[i+1] != countries[i]){ //Check if country is changing
                min7.push_back( 10000 ), max7.push_back( -10000 );    //If at last, the values are like that it mean7s no data collected about it.
                mean7.push_back( totalVector[countryNo].hospPatients / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) );   //Adding average value to vector
                countryNo++;
                totalVector[countryNo].howManyElementsFromThatCountry = 0;
                totalVector[countryNo].hospPatients = 0.0;
            }
            continue;
        }
        if( stoi( hosp_patients[i] ) < min7[countryNo] )    min7[countryNo] = stoi( hosp_patients[i] );
        if( stoi( hosp_patients[i] ) > max7[countryNo] )    max7[countryNo] = stoi( hosp_patients[i] );
        totalVector[countryNo].hospPatients += stod( hosp_patients[i] );  //Total of reproductionRate to calculate average.
        totalVector[countryNo].howManyElementsFromThatCountry++;
    }
    
    //FINDING VARIATION
    variationValue7.resize(dates.size());
    countryNo=0;
    filestream << "\nQUESTION7- HOSP_PATIENTS\nCOUNTRY MINIMUM MAXIMUM AVERAGE VARIATION" << endl;
    double sum=0;
    for(size_t i=0; i<dates.size(); i++){
        if(hosp_patients[i] != "")
            sum += pow( stod(hosp_patients[i])-mean7[countryNo], 2);
        if(countries[i+1] != countries[i]){
            variationValue7[countryNo] = sum/(totalVector[countryNo].howManyElementsFromThatCountry-1.0);
            if(min7[countryNo] == 10000) //Then also there is no average or variation data.
                filestream << totalVector[countryNo].country << " NO INFO NO INFO NO INFO NO INFO" << endl;
            else    
                filestream << totalVector[countryNo].country << " " << min7[countryNo] << " " << max7[countryNo] << " " << mean7[countryNo] << " " << variationValue7[countryNo] << endl;
            sum = 0;    
            countryNo++; 
        }
    }

}

void CovidData::question8(rapidcsv::Document doc){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(2); //Like %.2f c++ version
    CovidData::weekly_icu_admissions = doc.GetColumn<string>("weekly_icu_admissions");

    int countryNo = 0;
    totalVector[countryNo].howManyElementsFromThatCountry = 0;  //We will divide sum to it to find average value.
    totalVector[countryNo].weeklyIcu = 0;   //Total value for all countries. When we divide it to howManyElementsFromThatCountry, we will find average.
    min8.push_back( 10000 ), max8.push_back( -10000 );
    for(size_t i=0; i<dates.size(); i++){
        if(weekly_icu_admissions[i] == ""){      //If there is no data about it 
            if(countries[i+1] != countries[i]){ //Check if country is changing
                min8.push_back( 10000 ), max8.push_back( -10000 );    //If at last, the values are like that it mean8s no data collected about it.
                mean8.push_back( totalVector[countryNo].weeklyIcu / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) );   //Adding average value to vector
                countryNo++;
                totalVector[countryNo].howManyElementsFromThatCountry = 0;
                totalVector[countryNo].weeklyIcu = 0.0;
            }
            continue;
        }
        if( stoi( weekly_icu_admissions[i] ) < min8[countryNo] )    min8[countryNo] = stoi( weekly_icu_admissions[i] );
        if( stoi( weekly_icu_admissions[i] ) > max8[countryNo] )    max8[countryNo] = stoi( weekly_icu_admissions[i] );
        totalVector[countryNo].weeklyIcu += stod( weekly_icu_admissions[i] );  //Total of reproductionRate to calculate average.
        totalVector[countryNo].howManyElementsFromThatCountry++;
    }
    
    //FINDING VARIATION
    variationValue8.resize(dates.size());
    countryNo=0;
    filestream << "\nQUESTION8- weekly_icu_admissions\nCOUNTRY MINIMUM MAXIMUM AVERAGE VARIATION" << endl;
    double sum=0;
    for(size_t i=0; i<dates.size(); i++){
        if(weekly_icu_admissions[i] != "")
            sum += pow( stod(weekly_icu_admissions[i])-mean8[countryNo], 2);
        if(countries[i+1] != countries[i]){
            variationValue8[countryNo] = sum/(totalVector[countryNo].howManyElementsFromThatCountry-1.0);
            if(min8[countryNo] == 10000) //Then also there is no average or variation data.
                filestream << totalVector[countryNo].country << " NO INFO NO INFO NO INFO NO INFO" << endl;
            else    
                filestream << totalVector[countryNo].country << " " << min8[countryNo] << " " << max8[countryNo] << " " << mean8[countryNo] << " " << variationValue8[countryNo] << endl;
            sum = 0;    
            countryNo++; 
        }
    }

}


void CovidData::question9(rapidcsv::Document doc){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(2); //Like %.2f c++ version
    CovidData::weekly_hosp_admissions = doc.GetColumn<string>("weekly_hosp_admissions");

    int countryNo = 0;
    totalVector[countryNo].howManyElementsFromThatCountry = 0;  //We will divide sum to it to find average value.
    totalVector[countryNo].weeklyHospAdmis = 0;   //Total value for all countries. When we divide it to howManyElementsFromThatCountry, we will find average.
    min9.push_back( 10000 ), max9.push_back( -10000 );
    for(size_t i=0; i<dates.size(); i++){
        if(weekly_hosp_admissions[i] == ""){      //If there is no data about it 
            if(countries[i+1] != countries[i]){ //Check if country is changing
                min9.push_back( 10000 ), max9.push_back( -10000 );    //If at last, the values are like that it mean9s no data collected about it.
                mean9.push_back( totalVector[countryNo].weeklyHospAdmis / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) );   //Adding average value to vector
                countryNo++;
                totalVector[countryNo].howManyElementsFromThatCountry = 0;
                totalVector[countryNo].weeklyHospAdmis = 0.0;
            }
            continue;
        }
        if( stoi( weekly_hosp_admissions[i] ) < min9[countryNo] )    min9[countryNo] = stoi( weekly_hosp_admissions[i] );
        if( stoi( weekly_hosp_admissions[i] ) > max9[countryNo] )    max9[countryNo] = stoi( weekly_hosp_admissions[i] );
        totalVector[countryNo].weeklyHospAdmis += stod( weekly_hosp_admissions[i] );  //Total of weekly_hosp_admissions to calculate average.
        totalVector[countryNo].howManyElementsFromThatCountry++;
    }
    
    //FINDING VARIATION
    variationValue9.resize(dates.size());
    countryNo=0;
    filestream << "\nQUESTION9- weekly_hosp_admissions\nCOUNTRY MINIMUM MAXIMUM AVERAGE VARIATION" << endl;
    double sum=0;
    for(size_t i=0; i<dates.size(); i++){
        if(weekly_hosp_admissions[i] != "")
            sum += pow( stod(weekly_hosp_admissions[i])-mean9[countryNo], 2);
        if(countries[i+1] != countries[i]){
            variationValue9[countryNo] = sum/(totalVector[countryNo].howManyElementsFromThatCountry-1.0);
            if(min9[countryNo] == 10000) //Then also there is no average or variation data.
                filestream << totalVector[countryNo].country << " NO INFO NO INFO NO INFO NO INFO" << endl;
            else    
                filestream << totalVector[countryNo].country << " " << min9[countryNo] << " " << max9[countryNo] << " " << mean9[countryNo] << " " << variationValue9[countryNo] << endl;
            sum = 0;    
            countryNo++; 
        }
    }

}

void CovidData::question10(rapidcsv::Document doc){
    CovidData::new_tests = doc.GetColumn<string>("new_tests");

    int countryNo = 0;
    totalVector[countryNo].howManyElementsFromThatCountry = 0;  //We will divide sum to it to find average value.
    totalVector[countryNo].newTestPerDay = 0;   //Total value for all countries. When we divide it to howManyElementsFromThatCountry, we will find average.
    min10.push_back( 1000000 ), max10.push_back( -1000000 );

    for(size_t i=0; i<dates.size(); i++){
        if(new_tests[i] == ""){      //If there is no data about it 
            if(countries[i+1] != countries[i]){ //Check if country is changing
                min10.push_back( 1000000 ), max10.push_back( -1000000 );    //If at last, the values are like that it mean10s no data collected about it.
                mean10.push_back( totalVector[countryNo].newTestPerDay / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) );   //Adding average value to vector
                countryNo++;
                totalVector[countryNo].howManyElementsFromThatCountry = 0;
                totalVector[countryNo].newTestPerDay = 0.0;
            }
            continue;
        }
        if( stol( new_tests[i] ) < min10[countryNo] )    min10[countryNo] = stol( new_tests[i] );
        if( stol( new_tests[i] ) > max10[countryNo] )    max10[countryNo] = stol( new_tests[i] );
        totalVector[countryNo].newTestPerDay += stol( new_tests[i] );  //Total of new_tests to calculate average.
        totalVector[countryNo].howManyElementsFromThatCountry++;
        if(countries[i+1] != countries[i]){ //Check if country is changing
            min10.push_back( 1000000 ), max10.push_back( -1000000 );    //If at last, the values are like that it mean10s no data collected about it.
            mean10.push_back( totalVector[countryNo].newTestPerDay / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) );   //Adding average value to vector
            countryNo++;
            totalVector[countryNo].howManyElementsFromThatCountry = 0;
            totalVector[countryNo].newTestPerDay = 0.0;
        }
    }
    
    //FINDING VARIATION
    variationValue10.resize(dates.size());
    countryNo=0;
    filestream << "\nQUESTION10- new_tests\nCOUNTRY min10IMUM MAXIMUM AVERAGE VARIATION" << endl;
    double sum=0;
    for(size_t i=0; i<dates.size(); i++){
        if(new_tests[i] != "")
            sum += pow( stol(new_tests[i])-mean10[countryNo], 2);
        if(countries[i+1] != countries[i]){
            variationValue10[countryNo] = sum/(totalVector[countryNo].howManyElementsFromThatCountry-1.0);
            if(min10[countryNo] == 1000000 || max10[countryNo] == -1000000) //Then also there is no average or variation data.
                filestream << totalVector[countryNo].country << " NO INFO NO INFO NO INFO NO INFO" << endl;
            else    
                filestream << totalVector[countryNo].country << " " << min10[countryNo] << " " << max10[countryNo] << " " << mean10[countryNo] << " " << variationValue10[countryNo] << endl;
            sum = 0;    
            countryNo++; 
        }
    }

}

void CovidData::question11(rapidcsv::Document doc){
    CovidData::total_tests = doc.GetColumn<string>("total_tests");
    int countryNo = 0;

    filestream << "\nQUESTION11- Total Tests\n";
    for(size_t i=0; i<dates.size(); i++){
        if( total_tests[i] != "" )
            totalVector[countryNo].totalTests = stoi( total_tests[i] ); //data in the last saved day converting to integer.
        else if( total_tests[i] == "" ){
            if(countries[i+1] != countries[i]){
                if(totalVector[countryNo].totalTests==0) filestream << "Country: " << totalVector[countryNo].country << " Total Tests: NO INFO\n";    //If no info about tests
                else                                     filestream << "Country: " << totalVector[countryNo].country << " Total Tests: " << totalVector[countryNo].totalTests << endl;
                countryNo++;    //enter to the next country
            }
            continue;
        }
        if(countries[i+1] != countries[i]){
            totalVector[countryNo].totalTests = stoi( total_tests[i] ); //data in the last day
            if(totalVector[countryNo].totalTests==0) filestream << "Country: " << totalVector[countryNo].country << " Total Tests: NO INFO\n";    //If no info about tests
            else                                     filestream << "Country: " << totalVector[countryNo].country << " Total Tests: " << totalVector[countryNo].totalTests << endl; 
            countryNo++;    //enter to the next country
        }
    }

}

void CovidData::question12(rapidcsv::Document doc){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(4); //Like %.2f c++ version
    CovidData::positive_rate = doc.GetColumn<string>("positive_rate");

    double countryNo = 0;
    totalVector[countryNo].howManyElementsFromThatCountry = 0;  //We will divide sum to it to find average value.
    totalVector[countryNo].positiveRate = 0;   //Total value for all countries. When we divide it to howManyElementsFromThatCountry, we will find average.
    min12.push_back( 10000 ), max12.push_back( -10000 );
    for(size_t i=0; i<dates.size(); i++){
        if(positive_rate[i] == ""){      //If there is no data about it 
            if(countries[i+1] != countries[i]){ //Check if country is changing
                min12.push_back( 10000 ), max12.push_back( -10000 );    //If at last, the values are like that it mean12s no data collected about it.
                mean12.push_back( totalVector[countryNo].positiveRate / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) );   //Adding average value to vector
                countryNo++;
                totalVector[countryNo].howManyElementsFromThatCountry = 0;
                totalVector[countryNo].positiveRate = 0.0;
            }
            continue;
        }
        if( stod( positive_rate[i] ) < min12[countryNo] )    min12[countryNo] = stod( positive_rate[i] );
        if( stod( positive_rate[i] ) > max12[countryNo] )    max12[countryNo] = stod( positive_rate[i] );
        totalVector[countryNo].positiveRate += stod( positive_rate[i] );  //Total of positive_rate to calculate average.
        totalVector[countryNo].howManyElementsFromThatCountry++;
    }
    
    //FINDING VARIATION
    variationValue12.resize(dates.size());
    countryNo=0;
    filestream << "\nQUESTION12- positive_rate\nCOUNTRY MINIMUM MAXIMUM AVERAGE VARIATION" << endl;
    double sum=0;
    for(size_t i=0; i<dates.size(); i++){
        if(positive_rate[i] != "")
            sum += pow( stod(positive_rate[i])-mean12[countryNo], 2);
        if(countries[i+1] != countries[i]){
            variationValue12[countryNo] = sum/(totalVector[countryNo].howManyElementsFromThatCountry-1.0);
            if(min12[countryNo] == 10000) //Then also there is no average or variation data.
                filestream << totalVector[countryNo].country << " NO INFO NO INFO NO INFO NO INFO" << endl;
            else    
                filestream << totalVector[countryNo].country << " " << min12[countryNo] << " " << max12[countryNo] << " " << mean12[countryNo] << " " << variationValue12[countryNo] << endl;
            sum = 0;    
            countryNo++; 
        }
    }

}

void CovidData::question13(rapidcsv::Document doc){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(2); //Like %.2f c++ version
    CovidData::tests_per_case = doc.GetColumn<string>("tests_per_case");

    double countryNo = 0;
    totalVector[countryNo].howManyElementsFromThatCountry = 0;  //We will divide sum to it to find average value.
    totalVector[countryNo].testPerCase = 0;   //Total value for all countries. When we divide it to howManyElementsFromThatCountry, we will find average.
    min13.push_back( 10000 ), max13.push_back( -10000 );
    for(size_t i=0; i<dates.size(); i++){
        if(tests_per_case[i] == ""){      //If there is no data about it 
            if(countries[i+1] != countries[i]){ //Check if country is changing
                min13.push_back( 10000 ), max13.push_back( -10000 );    //If at last, the values are like that it mean13s no data collected about it.
                mean13.push_back( totalVector[countryNo].testPerCase / (totalVector[countryNo].howManyElementsFromThatCountry*1.0) );   //Adding average value to vector
                countryNo++;
                totalVector[countryNo].howManyElementsFromThatCountry = 0;
                totalVector[countryNo].testPerCase = 0.0;
            }
            continue;
        }
        if( stod( tests_per_case[i] ) < min13[countryNo] )    min13[countryNo] = stod( tests_per_case[i] );
        if( stod( tests_per_case[i] ) > max13[countryNo] )    max13[countryNo] = stod( tests_per_case[i] );
        totalVector[countryNo].testPerCase += stod( tests_per_case[i] );  //Total of tests_per_case to calculate average.
        totalVector[countryNo].howManyElementsFromThatCountry++;
    }
    
    //FINDING VARIATION
    variationValue13.resize(dates.size());
    countryNo=0;
    filestream << "\nQUESTION13- tests_per_case\nCOUNTRY MINIMUM MAXIMUM AVERAGE VARIATION" << endl;
    double sum=0;
    for(size_t i=0; i<dates.size(); i++){
        if(tests_per_case[i] != "")
            sum += pow( stod(tests_per_case[i])-mean13[countryNo], 2);
        if(countries[i+1] != countries[i]){
            variationValue13[countryNo] = sum/(totalVector[countryNo].howManyElementsFromThatCountry-1.0);
            if(min13[countryNo] == 10000) //Then also there is no average or variation data.
                filestream << totalVector[countryNo].country << " NO INFO NO INFO NO INFO NO INFO" << endl;
            else    
                filestream << totalVector[countryNo].country << " " << min13[countryNo] << " " << max13[countryNo] << " " << mean13[countryNo] << " " << variationValue13[countryNo] << endl;
            sum = 0;    
            countryNo++; 
        }
    }

}

void CovidData::question14(rapidcsv::Document doc){
    CovidData::people_vaccinated = doc.GetColumn<string>("people_vaccinated");
    int countryNo = 0;

    filestream << "\nQUESTION14- People Vaccinated\n";
    for(size_t i=0; i<dates.size(); i++){
        if( people_vaccinated[i] != "" )
            totalVector[countryNo].vaccinated = stoi( people_vaccinated[i] ); //data in the last saved day converting to integer.
        else if( people_vaccinated[i] == "" ){
            if(countries[i+1] != countries[i]){
                if(totalVector[countryNo].vaccinated==0) filestream << "Country: " << totalVector[countryNo].country << " Total Vaccinated: NO INFO\n";    //If no info about Vaccinated
                else                                     filestream << "Country: " << totalVector[countryNo].country << " Total Vaccinated: " << totalVector[countryNo].vaccinated << endl;
                countryNo++;    //enter to the next country
            }
            continue;
        }
        if(countries[i+1] != countries[i]){
            totalVector[countryNo].vaccinated = stoi( people_vaccinated[i] ); //data in the last day
            if(totalVector[countryNo].vaccinated==0) filestream << "Country: " << totalVector[countryNo].country << " Total Vaccinated: NO INFO\n";    //If no info about Vaccinated
            else                                     filestream << "Country: " << totalVector[countryNo].country << " Total Vaccinated: " << totalVector[countryNo].vaccinated << endl; 
            countryNo++;    //enter to the next country
        }
    }

}


void CovidData::question15(rapidcsv::Document doc){
    CovidData::people_fully_vaccinated = doc.GetColumn<string>("people_fully_vaccinated");
    int countryNo = 0;

    filestream << "\nQUESTION15- people fully vaccinated \n";
    for(size_t i=0; i<dates.size(); i++){
        if( people_fully_vaccinated[i] != "" )
            totalVector[countryNo].fullVaccinated = stoi( people_fully_vaccinated[i] ); //data in the last saved day converting to integer.
        else if( people_fully_vaccinated[i] == "" ){
            if(countries[i+1] != countries[i]){
                if(totalVector[countryNo].fullVaccinated==0) filestream << "Country: " << totalVector[countryNo].country << " Total fully vaccinated: NO INFO\n";    //If no info about fully vaccinated
                else                                     filestream << "Country: " << totalVector[countryNo].country << " Total fully vaccinated: " << totalVector[countryNo].fullVaccinated << endl;
                countryNo++;    //enter to the next country
            }
            continue;
        }
        if(countries[i+1] != countries[i]){
            totalVector[countryNo].fullVaccinated = stoi( people_fully_vaccinated[i] ); //data in the last day
            if(totalVector[countryNo].fullVaccinated==0) filestream << "Country: " << totalVector[countryNo].country << " Total fully vaccinated: NO INFO\n";    //If no info about fully vaccinated
            else                                     filestream << "Country: " << totalVector[countryNo].country << " Total fully vaccinated: " << totalVector[countryNo].fullVaccinated << endl; 
            countryNo++;    //enter to the next country
        }
    }

}


void CovidData::question16(rapidcsv::Document doc){
    CovidData::total_vaccinations = doc.GetColumn<string>("total_vaccinations");
    int countryNo = 0;

    filestream << "\nQUESTION16- Total vaccinations\n";
    for(size_t i=0; i<dates.size(); i++){
        if( total_vaccinations[i] != "" )
            totalVector[countryNo].vaccinations = stoi( total_vaccinations[i] ); //data in the last saved day converting to integer.
        else if( total_vaccinations[i] == "" ){
            if(countries[i+1] != countries[i]){
                if(totalVector[countryNo].vaccinations==0) filestream << "Country: " << totalVector[countryNo].country << " Total vaccinations: NO INFO\n";    //If no info about vaccinations
                else                                     filestream << "Country: " << totalVector[countryNo].country << " Total vaccinations: " << totalVector[countryNo].vaccinations << endl;
                countryNo++;    //enter to the next country
            }
            continue;
        }
        if(countries[i+1] != countries[i]){
            totalVector[countryNo].vaccinations = stoi( total_vaccinations[i] ); //data in the last day
            if(totalVector[countryNo].vaccinations==0) filestream << "Country: " << totalVector[countryNo].country << " Total vaccinations: NO INFO\n";    //If no info about vaccinations
            else                                       filestream << "Country: " << totalVector[countryNo].country << " Total vaccinations: " << totalVector[countryNo].vaccinations << endl; 
            countryNo++;    //enter to the next country
        }
    }

}

void CovidData::question17(rapidcsv::Document doc){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(2); //Like %.2f c++ version
    CovidData::population = doc.GetColumn<string>("population");
    CovidData::median_age = doc.GetColumn<string>("median_age");
    CovidData::aged_65_older = doc.GetColumn<string>("aged_65_older");
    CovidData::aged_70_older = doc.GetColumn<string>("aged_70_older");
    CovidData::gdp_per_capita = doc.GetColumn<string>("gdp_per_capita");
    CovidData::extreme_poverty = doc.GetColumn<string>("extreme_poverty");
    CovidData::cardiovasc_death_rate = doc.GetColumn<string>("cardiovasc_death_rate");
    CovidData::diabetes_prevalence = doc.GetColumn<string>("diabetes_prevalence");
    CovidData::female_smokers = doc.GetColumn<string>("female_smokers");
    CovidData::male_smokers = doc.GetColumn<string>("male_smokers");
    CovidData::handwashing_facilities = doc.GetColumn<string>("handwashing_facilities");
    CovidData::hospital_beds_per_thousand = doc.GetColumn<string>("hospital_beds_per_thousand");
    CovidData::life_expectancy = doc.GetColumn<string>("life_expectancy");
    CovidData::human_development_index = doc.GetColumn<string>("human_development_index");

    
    filestream << "\nQUESTION17- Listing many information.\nCOUNTRY\tPopulation\tDensity\tMedian Age\tAged 65 Older\tAged 70 Older\tGdp Per Capita\tExtreme Poverty\tCardiovac Death Rate\t";
    filestream << "Diabetes Prevelance\tFemale Smokers\tMale Smokers\tHandwashing Facilities\tHospital Beds Per Thousand\tLife Expectancy\tHuman Development Index" << endl;

    int countryNo1=0, countryNo2=0, countryNo3=0, countryNo4=0, countryNo5=0, countryNo6=0, countryNo7=0, countryNo8=0, countryNo9=0, countryNo10=0, countryNo11=0, countryNo12=0, countryNo13=0, countryNo14=0;
    int indexThatContain = 0;
    for(size_t i=0; i<dates.size(); i++){
        indexThatContain = -1;
        //population
        if( population[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo1].population = stol(population[indexThatContain]);  filestream << countries[indexThatContain] << "\t"<< totalVector[countryNo1].population << "\t";  }
            else                    { totalVector[countryNo1].population = 10000;  filestream << countries[i] << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo1++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //median_age
        if( median_age[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo2].medianAge = stol(median_age[indexThatContain]);  filestream << totalVector[countryNo2].medianAge << "\t";  }
            else                    { totalVector[countryNo2].medianAge = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo2++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //aged_65_older
        if( aged_65_older[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo3].aged65Older = stol(aged_65_older[indexThatContain]);  filestream << totalVector[countryNo3].aged65Older << "\t";  }
            else                    { totalVector[countryNo3].aged65Older = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo3++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //aged_70_older
        if( aged_70_older[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo4].aged70Older = stol(aged_70_older[indexThatContain]);  filestream << totalVector[countryNo4].aged70Older << "\t";  }
            else                    { totalVector[countryNo4].aged70Older = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo4++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //gdp_per_capita
        if( gdp_per_capita[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo5].gdpPerCapita = stol(gdp_per_capita[indexThatContain]);  filestream << totalVector[countryNo5].gdpPerCapita << "\t";  }
            else                    { totalVector[countryNo5].gdpPerCapita = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo5++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //extreme_poverty
        if( extreme_poverty[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo6].extremePoverty = stol(extreme_poverty[indexThatContain]);  filestream << totalVector[countryNo6].extremePoverty << "\t";  }
            else                    { totalVector[countryNo6].extremePoverty = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo6++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //cardiovasc_death_rate
        if( cardiovasc_death_rate[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo7].cardiovascDeathRate = stol(cardiovasc_death_rate[indexThatContain]);  filestream << totalVector[countryNo7].cardiovascDeathRate << "\t";  }
            else                    { totalVector[countryNo7].cardiovascDeathRate = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo7++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //diabetes_prevalence
        if( diabetes_prevalence[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo8].diabetesPrevalence = stol(diabetes_prevalence[indexThatContain]);  filestream << totalVector[countryNo8].diabetesPrevalence << "\t";  }
            else                    { totalVector[countryNo8].diabetesPrevalence = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo8++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //female_smokers
        if( female_smokers[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo9].femaleSmokers = stol(female_smokers[indexThatContain]);  filestream << totalVector[countryNo9].femaleSmokers << "\t";  }
            else                    { totalVector[countryNo9].femaleSmokers = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo9++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //male_smokers
        if( male_smokers[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo10].maleSmokers = stol(male_smokers[indexThatContain]);  filestream << totalVector[countryNo10].maleSmokers << "\t";  }
            else                    { totalVector[countryNo10].maleSmokers = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo10++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //handwashing_facilities
        if( handwashing_facilities[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo11].handwashingFacilities = stol(handwashing_facilities[indexThatContain]);  filestream << totalVector[countryNo11].handwashingFacilities << "\t";  }
            else                    { totalVector[countryNo11].handwashingFacilities = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo11++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //hospital_beds_per_thousand
        if( hospital_beds_per_thousand[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo12].hospitalBedsPerThousand = stol(hospital_beds_per_thousand[indexThatContain]);  filestream << totalVector[countryNo12].hospitalBedsPerThousand << "\t";  }
            else                    { totalVector[countryNo12].hospitalBedsPerThousand = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo12++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //life_expectancy
        if( life_expectancy[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo13].lifeExpectancy = stol(life_expectancy[indexThatContain]);  filestream << totalVector[countryNo13].lifeExpectancy << "\t";  }
            else                    { totalVector[countryNo13].lifeExpectancy = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo13++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
        }
        indexThatContain = -1;
        //human_development_index
        if( human_development_index[i] != "" ) indexThatContain = i;
        if(countries[i+1] != countries[i]){
            if(indexThatContain!=-1){ totalVector[countryNo14].humanDevelopmentIndex = stol(human_development_index[indexThatContain]);  filestream << totalVector[countryNo14].humanDevelopmentIndex << "\t";  }
            else                    { totalVector[countryNo14].humanDevelopmentIndex = 10000;  filestream << " NO INFO" << " "; } //10000 value will be used for no data.
            countryNo14++;    //enter to the next country
            indexThatContain = -1; //if next country doesn't have info print "no info"
            filestream << endl;
        }



    }


}

void CovidData::question18(){
    filestream.setf(ios::fixed), filestream.setf(ios::showpoint), filestream.precision(2); //Like %.2f c++ version

    filestream << "\nQuestion18\nCountry  q3 q4 q5_min q5_max q5_avg q5_var q6_min q6_max q6_avg q6_var q7_min q7_max pq7_avg q7_var q8_min q8_max q8_avg q8_var q9_min q9_max q9_avg q9_var ";
    filestream << "q10_min q10_max q10_avg q10_var q11 q12_min q12_max q12_avg q12_var q13_min q13_max q13_avg q13_var q14 q15 q16\t";
    filestream << "Population\tDensity\tMedian Age\tAged 65 Older\tAged 70 Older\tGdp Per Capita\tExtreme Poverty\tCardiovac Death Rate\t";
    filestream << "Diabetes Prevelance\tFemale Smokers\tMale Smokers\tHandwashing Facilities\tHospital Beds Per Thousand\tLife Expectancy\tHuman Development Index" << endl;

    int countryNo = 0;
    int indexThatContain = 0;
    for(size_t i=0; i<totalVector.size(); i++){
        //q1 q3 q4
        filestream << totalVector[countryNo].country << " " << totalVector[countryNo].cases << " " << totalVector[countryNo].deaths << " ";
        //q5
        if(min5[countryNo]!=10000)  filestream << min5[countryNo]  << " " << max5[countryNo]  << " " << mean5[countryNo]  << " " << variationValue5[countryNo]  << " ";
        else                        filestream << "NO INFO NO INFO NO INFO NO INFO ";
        //q6
        if(min6[countryNo]!=10000)  filestream << min6[countryNo]  << " " << max6[countryNo]  << " " << mean6[countryNo]  << " " << variationValue6[countryNo]  << " ";
        else                        filestream << "NO INFO NO INFO NO INFO NO INFO ";
        //q7
        if(min7[countryNo]!=10000)  filestream << min7[countryNo]  << " " << max7[countryNo]  << " " << mean7[countryNo]  << " " << variationValue7[countryNo]  << " ";
        else                        filestream << "NO INFO NO INFO NO INFO NO INFO ";
        //q8
        if(min8[countryNo]!=10000)  filestream << min8[countryNo]  << " " << max8[countryNo]  << " " << mean8[countryNo]  << " " << variationValue8[countryNo]  << " ";
        else                        filestream << "NO INFO NO INFO NO INFO NO INFO ";
        //q9
        if(min9[countryNo]!=10000)  filestream << min9[countryNo]  << " " << max9[countryNo]  << " " << mean9[countryNo]  << " " << variationValue9[countryNo]  << " ";
        else                        filestream << "NO INFO NO INFO NO INFO NO INFO ";
        //q10
        if(min10[countryNo]!=1000000) filestream << min10[countryNo] << " " << max10[countryNo] << " " << mean10[countryNo] << " " << variationValue10[countryNo] << " ";
        else                          filestream << "NO INFO NO INFO NO INFO NO INFO ";
        //q11
        if(totalVector[countryNo].totalTests==0) filestream << "NO INFO ";          
        else  filestream << totalVector[countryNo].totalTests << " ";
        //q12
        if(min12[countryNo]!=10000)  filestream << min12[countryNo] << " " << max12[countryNo] << " " << mean12[countryNo] << " " << variationValue12[countryNo] << " ";
        else                         filestream << "NO INFO NO INFO NO INFO NO INFO ";
        //q13
        if(min13[countryNo]!=10000)  filestream << min13[countryNo] << " " << max13[countryNo] << " " << mean13[countryNo] << " " << variationValue13[countryNo] << " ";
        else                         filestream << "NO INFO NO INFO NO INFO NO INFO ";
        //q14
        if(totalVector[countryNo].vaccinated==0)     filestream << "NO INFO ";  
        else                                         filestream << totalVector[countryNo].vaccinated << " ";   
        //q15
        if(totalVector[countryNo].fullVaccinated==0) filestream << "NO INFO ";
        else                                         filestream << totalVector[countryNo].fullVaccinated << " ";
        //q16
        if(totalVector[countryNo].vaccinations==0) filestream << "NO INFO "; 
        else                                       filestream << totalVector[countryNo].vaccinations << " ";   

        //q17
        if(totalVector[countryNo].population != 10000) filestream << totalVector[countryNo].population << "\t";  
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].medianAge != 10000) filestream << totalVector[countryNo].medianAge << "\t";  
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].aged65Older != 10000) filestream << totalVector[countryNo].aged65Older << "\t";  
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].aged70Older != 10000) filestream << totalVector[countryNo].aged70Older << "\t";  
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].gdpPerCapita != 10000) filestream << totalVector[countryNo].gdpPerCapita << "\t"; 
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].extremePoverty != 10000) filestream << totalVector[countryNo].extremePoverty << "\t"; 
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].cardiovascDeathRate != 10000) filestream << totalVector[countryNo].cardiovascDeathRate << "\t"; 
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].diabetesPrevalence != 10000) filestream << totalVector[countryNo].diabetesPrevalence << "\t";  
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].femaleSmokers != 10000) filestream << totalVector[countryNo].femaleSmokers << "\t";
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].maleSmokers != 10000) filestream << totalVector[countryNo].maleSmokers << "\t"; 
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].handwashingFacilities != 10000) filestream << totalVector[countryNo].handwashingFacilities << "\t";
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].hospitalBedsPerThousand != 10000) filestream << totalVector[countryNo].hospitalBedsPerThousand << "\t";
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].lifeExpectancy != 10000) filestream << totalVector[countryNo].lifeExpectancy << "\t";  
        else filestream << "NO INFO" << " ";
        if(totalVector[countryNo].humanDevelopmentIndex != 10000) filestream << totalVector[countryNo].humanDevelopmentIndex << "\t";
        else filestream << "NO INFO" << " ";

        countryNo++;
        filestream << endl;
    }
    filestream.close();
}
