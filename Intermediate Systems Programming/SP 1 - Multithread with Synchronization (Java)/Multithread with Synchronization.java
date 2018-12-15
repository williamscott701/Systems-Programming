
import java.util.Scanner;

//Generic Info Class
class GenericInfo {

    //declared the variables private to hide this from other classes
    private String name;
    private String city;

    //using this constructor to set the values of the variables when the object is created
    public GenericInfo(String name, String city) {
        this.name = name;
        this.city = city;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

}

//personal info class inheriting the generic info clas
class PersonalInfo extends GenericInfo {

    private String gender;
    private int age;

    //constructor
    public PersonalInfo(String gender, int age, String name, String city) {
        super(name, city);
        this.gender = gender;
        this.age = age;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

}

//family class inheriting the generic info class
class FamilyInfo extends GenericInfo {

    private String fatherName;
    private String motherName;

    //constructor
    public FamilyInfo(String fatherName, String motherName, String name, String city) {
        super(name, city);
        this.fatherName = fatherName;
        this.motherName = motherName;
    }

    public String getFatherName() {
        return fatherName;
    }

    public void setFatherName(String fatherName) {
        this.fatherName = fatherName;
    }

    public String getMotherName() {
        return motherName;
    }

    public void setMotherName(String motherName) {
        this.motherName = motherName;
    }

}

//Log class where we write and read data from Personal and Family classes
class Log {

    //creating objects of personal and family classes
    private PersonalInfo personalInfo;
    private FamilyInfo familyInfo;

    //writes the data to personal info object
    public void writePersonalInfo(String name, int age, String gender, String city) {
        //passing the variable values to constructor
        personalInfo = new PersonalInfo(gender, age, name, city);
    }

    //writes the data to family info object
    public void writeFamilyInfo(String name, String fatherName, String motherName, String city) {
        //passing the variable values to constructor
        familyInfo = new FamilyInfo(fatherName, motherName, name, city);
    }

    //print method, takes data from personal and family and prints them
    //Synchronizing a function helps managing the resources efficiently as it helps in mutual exclusion of shared resources
    //In this case when the print funciton is called by both t1 and t2 simultaneously, the synchronized will first let finish thread t1 and then allows t2 to handle this
    synchronized public void printCompleteInfo(String threadName) {
        System.out.println("\n----------------------------------------------\nCalling Thread: " + threadName + "\n----------------------------------------------");
        System.out.println("\nPersonal Info: \n------------------");
        System.out.println("Name: " + personalInfo.getName() + "\nCity: " + personalInfo.getCity() + "\nAge: " + personalInfo.getAge() + "\nGender: " + personalInfo.getGender());
        System.out.println("\nFamily Info: \n------------------");
        System.out.println("Name: " + familyInfo.getName() + "\nCity: " + familyInfo.getCity() + "\nFathers Name: " + familyInfo.getFatherName() + "\nMothers Name: " + familyInfo.getMotherName());
        System.out.println("\n");
    }
}

//extendint thread class as this will give us flexibility in the implementation of run method
public class SPL4 extends Thread {

    public static void main(String[] args) throws InterruptedException {

        Scanner in = new Scanner(System.in);

        Log log = new Log();

        //Aarya Stark,20,Female,Winterfell,Eddard Stark,Catyelyn Stark
        System.out.println("Limit: 6 Values");
        String input = in.nextLine();
        String split[] = input.split(",");
        while (split.length < 6) {
            System.out.println("Error! Please Enter only 6 values seperated by comma");
             input = in.nextLine();
             split = input.split(",");
        }
        
        String name = split[0], gender = split[2], city = split[3], fathersName = split[4], mothersName = split[5];

        int age = Integer.parseInt(split[1]);

        //creating Thread t1, this is implemented using lamba expressions in java 8. the run method is the first argument
        Thread t1 = new Thread(() -> {
            log.writeFamilyInfo(name, fathersName, mothersName, city);
            log.printCompleteInfo("Family Thread");
        });

        Thread t2 = new Thread(() -> {
            log.writePersonalInfo(name, age, gender, city);
            log.printCompleteInfo("Personal Thread");
        });

        //starting threads
        t1.start();
        t2.start();

    }

}
