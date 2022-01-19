package mat118_1801042656_hw2;
import java.io.*;
import java.util.*;

/** Note that all products are never loaded in memory in same time. */

public class SGFileHandler{
    /** List to hold infos in manufacturing_defects.txt */
    private ArrayList< ArrayList<Integer> > myList = new ArrayList< ArrayList<Integer>>();
    /** List to hold infos for cases and predicted cases to write temp.txt file. */
    private ArrayList< ArrayList<String> > toWrite = new ArrayList< ArrayList<String> >();
    /** How many data in all years in all compaines. */
    private int howManyTimesChecked = 0;

    /** Writing temp data to fileName file to transfer python file */
    public void writeToFile(String fileName){
        System.out.println(toWrite.toString());
        BufferedWriter bufferString;
 
        try{
            bufferString= new BufferedWriter( new FileWriter(fileName,false) ); //false is for removing content of file.
            for(int i=0; i<toWrite.size(); i++){
                for(int j=0; j<toWrite.get(i).size(); j++)
                    bufferString.write( toWrite.get(i).get(j) + "\t");
                bufferString.write("\n");   
            }
            bufferString.close();
        }  //End of try
        catch (IOException e) {
            System.out.println("File writing error. Check permissions.");
            e.printStackTrace();
        }   //End of catch

    }

    /** Reading infos in manufacturing_defects.txt */
    public void readFile(String fileName) {
        String readedLine; 

        try{
            BufferedReader bufferRead = new BufferedReader( new FileReader(fileName) );
            /** Reading all lines one by one. */
            for(int i=0; ( readedLine = bufferRead.readLine() ) != null && !readedLine.equals("\n") ; i++){
                /** Creating a list to hold the current line elements that seperated by (tab) */
                List<String> tempList = new ArrayList<String>();
                /** Splitting by tab character */
                tempList = Arrays.asList( readedLine.split("\\t") );
                System.out.println(tempList.toString());
                //System.out.println( tempList.toString() );
                if(tempList.size() > 1){ /** if line contains a empty character, don't enter the block. */
                    /** Creating a integer list to put all splitted string elements */
                    List<Integer> intList = new ArrayList<Integer>();
                    tempList.forEach(item -> intList.add(Integer.valueOf(item) ) );
                    /** Allocate memory */
                    myList.add( new ArrayList<Integer>() );
                    /** Adding all elements to list. */
                    for(int j=0; j<intList.size(); j++){
                        myList.get(i).add( intList.get(j) );
                    }
                }
            }
            bufferRead.close(); /** Closing reader to prevent source leaks. */
        }  //End of try
        catch (IOException e) {
            System.out.println("File reading error. Check permissions and file.");
            e.printStackTrace();
        }   //End of catch.

        /** Creating memory location for toWrite ArrayList. (They will be written to temp file.) */
        for(int i=0; i<=4; i++)
            toWrite.add( new ArrayList<String>() );
        

    }

    /** part a */
    public int getNumberOfDefects(int whichCase){
        int total = 0;
        for(int row=0; row<myList.size(); row++){
            for(int column=2; column<myList.get(column).size(); column++){ //Starting from column 2 because column0 and 1 doesn't show case.
                if(whichCase == myList.get(row).get(column))
                    total++;
            }
        }
        toWrite.get(whichCase).add( Integer.toString(whichCase) );
        toWrite.get(whichCase).add( Integer.toString(total) ); // writing cases to file as integer.
        return total;
    }

    /** part b */
    public float findRatePeriod(boolean printData){
        howManyTimesChecked = 0;
        int totalEvents = 0;
        for(int row=0; row<myList.size(); row++)
            for(int column=2; column<myList.get(column).size(); column++){ //Starting from column 2 because column0 and 1 doesn't show case.
                totalEvents += myList.get(row).get(column);
                howManyTimesChecked++;
            }
        
        float lambda = (float)totalEvents/howManyTimesChecked; /** events/time */
        if(printData == true)
            System.out.println("Total " + totalEvents + " events and " + howManyTimesChecked + " times, So mean(rate) = λ is " + lambda);
        return lambda;
    }

    /** part c */
    public double getPredictedCases(int whichCase){
        double result = 0, probability = 0;
        //false in parameter is to not printing data.
        double expLambda = Math.exp( -1 * findRatePeriod(false) ); // exp means e^(findRatePeriod) number from java.lang
        double lambdaToK = Math.pow( findRatePeriod(false) , whichCase);
        //Formula is -> λ^k * e^(-λ) / k!

        probability = expLambda * lambdaToK / factorial(whichCase);
        result = probability * howManyTimesChecked; //To find number of cases.
        // System.out.printf("Probability is %.2g | predicted cases is probability*timesChecked = %.2g", result, result*howManyTimesChecked);

        toWrite.get(whichCase).add( Integer.toString((int)result) ); // writing predicted cases to file as integer.
        return result;
    }

    /** Helper method to find factorial */
    public long factorial(int number){
        if(number <= 1) return 1;
        else  return number * factorial(number-1);
    }

    public int size(){
        return myList.size();
    }

}
