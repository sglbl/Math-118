import mat118_1801042656_hw2.*;
/**
 * @author Suleyman Golbol 1801042656
 * Driver class for hw2 in Math 118
 */

public class Main{
    private static SGFileHandler myFileHandler = new SGFileHandler();

    public static void main(String[] args){    
        myFileHandler.readFile("mat118_1801042656_hw2/manufacturing_defects.txt");

        System.out.println("\n--PART A--");
        partA();
        System.out.println("\n--PART B--");
        partB();
        System.out.println("\n--PART C--");
        partC();
        System.out.println("--PART D--");
        partD();

    }//End of main.

    public static void partA(){
        for(int i=0; i<=4; i++)
            System.out.println("For # of defects for " + i + ", number of cases: " + myFileHandler.getNumberOfDefects(i) );
    }

    public static void partB(){
        System.out.println("Mean(rate) = λ is " + myFileHandler.findRatePeriod(true /* true is for printing data */)); 
    }

    public static void partC(){
        for(int i=0; i<=4; i++)
            System.out.printf("For # of defects for %d\tpredicted # of cases: %.4g \n",
                                i, myFileHandler.getPredictedCases(i));
    }

    public static void partD(){
        myFileHandler.writeToFile("mat118_1801042656_hw2/temp.txt"); // Writing to temp.txt file the infos to handle them in python.
        System.out.println("Calling python script to run part D.\n");
    }

    
}