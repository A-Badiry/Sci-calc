    //
//  main.c
//  Sci-Calculator
//
//  Created by achraf badiry on 10/21/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#define PI 3.14159265358979323846

//Define a structure for a node in the linked list
typedef struct Node {
    char data;
    struct Node *next;
} Node;

 

//Prototype declarations of the functions used.
double ExpressionAddSub(Node *head);
double ExpressionMultDiv(Node *head);
void ParseExpressionMultDiv(void);
void ParseExpressionAddSub(void);
void Append(Node **head, char data);
void FreeList(Node *head);
void ChooseOp(void);
void ReadMem(void);
void Modulo(void);
void Sqrt(void);
void Sin(void);
void Abs(void);
void Cos(void);
void Tan(void);
void ArcSin(void);
void ArcCos(void);
void ArcTan(void);
void Ln(void);
void Exp(void);
void Log(void);
void Fact(void);
void PrimeFact(void);





//Global variables to store the data in files
static char angle_unit = 'R';
static double mem_value;
//––––––––––––––––––––––––––––––––––––––––––––

//Global file pointers
FILE *ang;
FILE *mem;
FILE *hasrun;
//–––––––––––––––––––––


// Conversion factors for length, area, volume, weight, and temperature

// Inches to centimeters, centimeters to inches
const double lengthFactors[2] = {2.54, 1 / 2.54};
// Sq. feet to sq. meters, sq. meters to sq. feet
const double areaFactors[2] = {0.092903, 1 / 0.092903};
// Cubic inches to liters, liters to cubic inches
const double volumeFactors[2] = {0.016387, 1 / 0.016387};
// Pounds to kilograms, kilograms to pounds
const double weightFactors[2] = {0.453592, 1 / 0.453592};
// Fahrenheit to Celsius, Celsius to Fahrenheit
const double tempFactors[2] = {5.0 / 9.0, 9.0 / 5.0};
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––



// Function to add a character to the linked list
void Append(Node **head, char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *lastNode = *head;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
}



// Function to free the linked list memory
void FreeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}




// Function to check the configuration of the calculator, Function only runs once in the lifetime of the program !
void CheckConfig(void){
    
    char ch;
    
    hasrun = fopen("hasrun.txt","r");
    
    if (hasrun == NULL) {
        printf("Error opening the configuration file (default angle unit RAD, Value stored in mem. is 0).\n\n");
    }
    else
        ch = fgetc (hasrun);
        

    
    if (ch == '0')
    {
        printf("Welcome to Sci-Calc, Please choose configuration !\n\n");
        
        //Setting the calculator's angle unit
        ang = fopen("Angles.txt","w");
        
        if (ang == NULL)
        {
            printf("There was an error setting the angle unit, default unit : RAD\n\n");
            return;
        }
        
        else
        {
            printf("Please choose angle unit: ""D"" for Degrees ""R"" for Radians and ""G"" for gradians !\n ");
        correctconfang:
            scanf("%c",&angle_unit);
            
            if(angle_unit == 'D' || angle_unit == 'R' || angle_unit == 'G')
            {
                fputc(angle_unit,ang);
                fclose(ang);
            }
            else
            {
                printf("Wrong choice. Please choose either D or R or G !\n");
                goto correctconfang;
            }
            ang = fopen("Angles.txt","r");
        }
        
        //Setting an initial value to the memory
        mem = fopen("Memory.bin","wb");
        
        if (mem == NULL)
        {
            printf("There has been an error accessing the memory !\n");
        }
        
        else
        {
            
            printf("Please give initial number you want to store in memory : \n");
            scanf("%lf",&mem_value);
            fwrite(&mem_value, sizeof(double), 1, mem);
            fclose(mem);
        }
            
            mem = fopen("Memory.bin","rb");
            
        //Setting the character in "hasrun.txt" to 1 such that the function never runs again in the future !
            fclose(hasrun);
            hasrun = fopen ("hasrun.txt","w");
            fputc(1,hasrun);
            fclose(hasrun);
    }
        
        //Opening the two files in read mode as we will need them for multiple functions !
        ang = fopen("Angles.txt","r");
        mem = fopen("Memory.bin","rb");

return ;
}
    
        
    
    
    
    




//Function to chose the suitable operations
void ChooseOp(void){
    
    int operation;
   
correctop:
    printf("Please choose the expression operators: \n\n  ");
    printf("1.Addition and Substraction\n  2.Multiplication and Division\n  3.Modulo\n  4.SquareRoot of a number\n  5.ABS of a number\n  6.PrimeFact of a number\n  0.Exit\n\n");
    scanf("%d",&operation);
    
    switch (operation){
        case 1 : getchar();ParseExpressionAddSub();
            break;
        case 2 : getchar();ParseExpressionMultDiv();
            break;
        case 3 : Modulo();
            break;
        case 4 : Sqrt();
            break;
        case 5 : Abs();
            break;
        case 6: PrimeFact();
            break;
        case 0: return;
            break;
        default : printf("Please select a number from the list !");
            goto correctop;
    }
        
    
    
}



//Function to choose from mathematical functions
void Choosefct(void){
    
    int function;
    
    
    printf("Choose a function:\n  1.Sin()\n  2.Cos()\n  3.Tan()\n  4.arcSin()\n  5.arcCos()\n  6.arcTan()\n  7.Log[10]()\n  8.Ln()\n  9.Exp()\n  0.Exit\n\n");
correctchoice:
    scanf("%i",&function);
    
    if (function == 1)
    {
        Sin();
    }

    else if (function == 2)
    {
        Cos();
    }
    
    else if (function == 3)
    {
        Tan();
    }
    
    else if (function == 4)
    {
        ArcSin();
    }
    
    else if (function == 5)
    {
        ArcCos();
    }
    
    else if (function == 6)
    {
        ArcTan();
    }
    
    else if (function == 7)
    {
        Log();
    }

    else if (function == 8)
    {
        Ln();
    }
    
    else if (function == 9)
    {
        Exp();
    }

    else if (function == 0)
    {
        return;
    }

    else
    {
        printf("Please choose a number from the list !\n");
        goto correctchoice;
    }
    
    return;
}



// Function to edit configuration
void Edit(void)
{
    
    int n;
    
    printf("Please choose what do you want to configure:\n\n  1.Angle Unit\n  2.Memory Value\n  0.Exit\n\n");
    
correctedit:
    scanf("%i",&n);
    
    //re-setting the calculator's angle unit !
    if (n == 1)
        {
            fclose(ang);
            ang = fopen("Angles.txt","w");
            
            if (ang == NULL)
            {
                printf("There was an error setting the angle unit !\n");
                return;
            }
            
            else
            {
                printf("Please choose angle unit: ""D"" for Degrees ""R"" for Radians and ""G"" for gradians !\n ");
        correcteditang:
                getchar();
                scanf("%c",&angle_unit);
                
                if(angle_unit == 'D' || angle_unit == 'R' || angle_unit == 'G')
                {
                    fputc(angle_unit,ang);
                    fclose(ang);
                }
                else
                {
                    printf("Wrong choice. Please choose either D or R or G !\n");
                    goto correcteditang;
                }
                ang = fopen("Angles.txt","r");
            }
        return;
        }

        //Setting the new value to store in memory !
        else if(n == 2)
        {
            fclose(mem);
            mem = fopen("Memory.bin","wb");
            
            if (mem == NULL)
            {
                printf("There was a problem accessing memory !\n");
                return;
            }
            
            else
            {
                
                printf("Please give the number you want to store in memory : ");
                scanf("%lf",&mem_value);
                
                fwrite(&mem_value, sizeof(double), 1, mem);
                fclose(mem);
                
                mem = fopen("Memory.bin","rb");
            }
            return;
            
        }

        else if (n == 0)
        {
            return;
        }
            
        else 
        {
            printf("\nWrong choice, please chose either 1 or 2\n");
            goto correctedit;
        }
    
    return;
}





//Function to perform conversions
void Convert(void) {
    int choice;
    double value;

    printf("\nEnter the value to convert: ");
    scanf("%lf", &value);


    printf("Welcome to the unit converter!\n");
    printf("Select the conversion:\n");
    printf(" 1. Length: US system to Metric\n");
    printf(" 2. Length: Metric to US system\n");
    printf(" 3. Area: US system to Metric\n");
    printf(" 4. Area: Metric to US system\n");
    printf(" 5. Volume: US system to Metric\n");
    printf(" 6. Volume: Metric to US system\n");
    printf(" 7. Weight: US system to Metric\n");
    printf(" 8. Weight: Metric to US system\n");
    printf(" 9. Temperature: US system to Metric\n");
    printf("10. Temperature: Metric to US system\n");
    printf(" 0. Exit\n\n");


correctconv: 
    printf("Enter your choice (1 to 10): ");
    scanf("%d", &choice);

    

    switch (choice) 
    {
        case 1:
        case 2:
            printf("%.2f %s is equal to %.2f %s.\n", value, (choice == 1) ? "inches" : "centimeters", value * lengthFactors[choice - 1], (choice == 1) ? "centimeters" : "inches");
            break;

        case 3:
        case 4:
            printf("%.2f %s is equal to %.2f %s.\n", value, (choice == 3) ? "square feet" : "square meters", value * areaFactors[choice - 3], (choice == 3) ? "square meters" : "square feet");
            break;

        case 5:
        case 6:
            printf("%.2f %s is equal to %.2f %s.\n", value, (choice == 5) ? "cubic inches" : "liters", value * volumeFactors[choice - 5], (choice == 5) ? "liters" : "cubic inches");
            break;

        case 7:
        case 8:
            printf("%.2f %s is equal to %.2f %s.\n", value, (choice == 7) ? "pounds" : "kilograms", value * weightFactors[choice - 7], (choice == 7) ? "kilograms" : "pounds");
            break;

        case 9:
        case 10:
            printf("%.2f %s is equal to %.2f %s.\n", value, (choice == 9) ? "Fahrenheit" : "Celsius", value * tempFactors[choice - 9], (choice == 9) ? "Celsius" : "Fahrenheit");
            break;

        case 0: return;
            break;
        
        default:
            printf("\n\nInvalid choice. Please select a number from 1 to 10.\n");
            goto correctconv;
    }

    
}

//Function to read the value stored in memory
void ReadMem(void){
    
    double value;

    mem = fopen("Memory.bin","rb");
    
    if (mem == NULL)
    {
        printf("Error accessing memory !");
        return;
    }
    
    else
    {
    fread(&value, sizeof(double), 1, mem);
    printf("Value in Memory : %lf",value);
    return;
    }
    
}



//–––––––––––––––––––––––––––––––––––––––––––– START OF MATHEMATICAL FUNCTIONS ––––––––––––––––––––––––––––––––––––––––––––––


//Function that calculates the modulo of 2 numbers
void Modulo(void){
    
    int a,b,modulo;
    
    printf("\nType the two integers in the correct order: ");
    scanf("%i %i",&a,&b);
    
    modulo = a%b;
    
    printf("\n%i mod(%i) = %i\n\n",a,b,modulo);

}

//Function that calculates the the square root of a number
void Sqrt(void){
    
    double n;
    
    printf("\nType in your number: ");
    scanf("%lf",&n);
    
    printf("\nsqrt(%lf)= %lf\n\n",n,sqrt(n));

    
}

//Function calculating the absolute value of a number
void Abs(void){
    
    double n;
    
    printf("\nType in your number: ");
    scanf("%lf",&n);
    printf("\nabs(%lf)= %lf\n\n",n,fabs(n));
    
}

//Function calculating the sine of a value
void Sin(void){
    char ch;
    double n,entry;
    
    printf("\nType in your number: ");
    scanf("%lf",&entry);
    n = entry;

    //This part is for checking wich angle unit to work with and convert the input accordingly
    ang = fopen("Angles.txt","r");
    if (ang == NULL)
    {
        printf("Error accessing memory ! Calculating for value in RAD\n\n");
        printf("sin(%lf)= %lf\n\n",entry,sin(n));
        return;
    }

    else
    {
        ch = fgetc(ang);

        if (ch == 'D')
        {   
            n = n * (PI/180.0);
            printf("\nsin(%lf)= %lf\n\n",entry,sin(n));
        }

        else if (ch == 'G')
        {
            n = (n/200) * PI;
            printf("\nsin(%lf)= %lf\n\n",entry,sin(n));

        }
        
        else if (ch == 'R')
        {
            printf("\nsin(%lf)= %lf\n\n",entry,sin(n));
        }

        else
        {
            printf("Angles settings invalid !!! Calculating for value in RAD\n\n");
            printf("sin(%lf)= %lf\n\n",entry,sin(n));
        }

        return;
    }

    
    
}


//Function to calculate the cosine of a number
void Cos(void)
{
    char ch;
    double n,entry;
    
    printf("\nType in your number: ");
    scanf("%lf",&entry);
    n = entry;

    //This part is for checking wich angle unit to work with and convert the input accordingly
    ang = fopen("Angles.txt","r");
    if (ang == NULL)
    {
        printf("Error accessing memory ! Calculating for value in RAD\n\n");
        printf("cos(%lf)= %lf\n\n",entry,cos(n));
        return;
    }

    else
    {
        ch = fgetc(ang);

        if (ch == 'D')
        {   
            n = n * (PI/180.0);
            printf("\ncos(%lf)= %lf\n\n",entry,cos(n));
        }

        else if (ch == 'G')
        {
            n = (n/200) * PI;
            printf("\ncos(%lf)= %lf\n\n",entry,cos(n));

        }
        
        else if (ch == 'R')
        {
            printf("\ncos(%lf)= %lf\n\n",entry,cos(n));
        }

        else
        {
            printf("Angles settings invalid !!! Calculating for value in RAD\n\n");
            printf("cos(%lf)= %lf\n\n",entry,cos(n));
        }

        return;
    
    }

}

//Function that calculates the tangent of a number
void Tan(void){
    
    char ch;
    double n,entry;
    
    printf("\nType in your number: ");
    scanf("%lf",&entry);
    n = entry;

    //This part is for checking wich angle unit to work with and convert the input accordingly
    ang = fopen("Angles.txt","r");
    if (ang == NULL)
    {
        printf("Error accessing memory ! Calculating for value in RAD\n\n");
        printf("tan(%lf)= %lf\n\n",entry,tan(n));
        return;
    }

    else
    {
        ch = fgetc(ang);

        if (ch == 'D')
        {   
            n = n * (PI/180.0);
            printf("\ntan(%lf)= %lf\n\n",entry,tan(n));
        }

        else if (ch == 'G')
        {
            n = (n/200) * PI;
            printf("\ntan(%lf)= %lf\n\n",entry,tan(n));

        }
        
        else if (ch == 'R')
        {
            printf("\ntan(%lf)= %lf\n\n",entry,tan(n));
        }

        else
        {
            printf("Angles settings invalid !!! Calculating for value in RAD\n\n");
            printf("tan(%lf)= %lf\n\n",entry,tan(n));
        }

        return;
    
    }

}


//Function that calculates the arc-sine of a number
void ArcSin(void){
    
    char ch;
    double n, angle;
    
    printf("\nType in your number: ");
    scanf("%lf",&n);
    
    angle = asin(n);

    //This part is for checking wich angle unit to work with and convert the output accordingly
    ang = fopen("Angles.txt","r");

    if (ang == NULL)
    {
        printf("Error accessing memory ! Calculating the value in RAD\n\n");
        printf("arcsin(%lf)= %lf\n\n",n,angle);
        return;
    }

    else
    {
        ch = fgetc(ang);

        if (ch == 'D')
        {   
            angle = angle * (180.0/PI);
            printf("\narcsin(%lf)= %lf\n\n",n,angle);
        }

        else if (ch == 'G')
        {
            angle = (angle*200) / PI;
            printf("\narcsin(%lf)= %lf\n\n",n,angle);

        }
        
        else if (ch == 'R')
        {
            printf("\narcsin(%lf)= %lf\n\n",n,angle);
        }

        else
        {
            printf("Angles settings invalid !!! Calculating the value in RAD\n\n");
            printf("arcsin(%lf)= %lf\n\n",n,angle);
        }

        return;


    }
    
}

//Function to calculate the arc-cosine of a number
void ArcCos(void){
    
    char ch;
    double n, angle;
    
    printf("\nType in your number: ");
    scanf("%lf",&n);
    
    angle = acos(n);
    
    //This part is for checking wich angle unit to work with and convert the output accordingly
    ang = fopen("Angles.txt","r");
    if (ang == NULL)
    {
        printf("Error accessing memory ! Calculating the value in RAD\n\n");
        printf("\narccos(%lf)= %lf\n\n",n,angle);
        return;
    }

    else
    {
        ch = fgetc(ang);

        if (ch == 'D')
        {   
            angle = angle * (180.0/PI);
            printf("\narccos(%lf)= %lf\n\n",n,angle);
        }

        else if (ch == 'G')
        {
            angle = (angle*200) / PI;
            printf("\narccos(%lf)= %lf\n\n",n,angle);

        }
        
        else if (ch == 'R')
        {
            printf("\narccos(%lf)= %lf\n\n",n,angle);
        }

        else
        {
            printf("Angles settings invalid !!! Calculating the value in RAD\n\n");
            printf("arccos%lf)= %lf\n\n",n,angle);
        }

        return;

    }

}

//Function to calculate the arc-tangent of a number
void ArcTan(void){
    
     char ch;
    double n, angle;
    
    printf("\nType in your number: ");
    scanf("%lf",&n);
    
    angle = atan(n);

    //This part is for checking wich angle unit to work with and convert the output accordingly
    ang = fopen("Angles.txt","r");
    if (ang == NULL)
    {
        printf("Error accessing memory ! Calculating the value in RAD\n\n");
        printf("arctan(%lf)= %lf\n\n",n,angle);
        return;
    }

    else
    {
        ch = fgetc(ang);

        if (ch == 'D')
        {   
            angle = angle * (180.0/PI);
            printf("\narctan(%lf)= %lf\n\n",n,angle);
        }

        else if (ch == 'G')
        {
            angle = (angle*200) / PI;
            printf("\narctan(%lf)= %lf\n\n",n,angle);

        }
        
        else if (ch == 'R')
        {
            printf("\narctan(%lf)= %lf\n\n",n,angle);
        }

        else
        {
            printf("Angles settings invalid !!! Calculating the value in RAD\n\n");
            printf("arctan(%lf)= %lf\n\n",n,angle);
        }

        return;

    }

}

//Function to calculate the natural logarithm of a function
void Ln(void){
    
    double n;
    
    printf("\nType in your number: ");
    scanf("%lf",&n);
    printf("\nln(%lf)= %lf\n\n",n,log(n));
    
}

//Function to calculate the exponential of a number
void Exp(void){
    
    double n;
    
    printf("\nType in your number: ");
    scanf("%lf",&n);
    printf("\nexp(%lf)= %lf\n\n",n,exp(n));
    
}

//Function to calculate the log bas 10 of a number
void Log(void){
    
    double n;
    
    printf("\nType in your number: ");
    scanf("%lf",&n);
    printf("\nlog[10](%lf)= %lf\n\n",n,log10(n));
    
}


//–––––––––––––––––––––––––––––––––––––––––––––– END OF MATHEMATICAL FUNCTIONS –––––––––––––––––––––––––––––––––––––––––––––––––



//Function to get the expression from user for mult and div
void ParseExpressionMultDiv(void) 
{
CorrectExp:
    Node *expression = NULL;
    printf("Enter an arithmetic expression (using *, /): ");
    char inputChar;
    while ((inputChar = getchar()) != '\n' && inputChar != EOF) {
        Append(&expression, inputChar);
    }
    
    //This part of the code checks that the user did not mix between (+ or -)and(* or /)
    bool containsAdd = false;
    bool containsSub = false;
    bool containsMult = false;
    bool containsDiv = false;
    Node *temp = expression;
    while (temp != NULL) {
        if (temp->data == '+')
        {
            containsAdd = true;
        }
        
        else if (temp->data == '-')
        {
            containsSub = true;
        }
        
        else if (temp->data == '*')
        {
            containsMult = true;
        }
        
        else if (temp->data == '/')
        {
            containsDiv = true;
        }
        
        temp = temp->next;
    }

    if (((containsAdd || containsSub) && (containsMult || containsDiv)) || containsSub == true || containsAdd == true) {
        printf("\nError: Operators + and - are not allowed here.\n\n");
        FreeList(expression);
        goto CorrectExp;
    }

    
    double result = ExpressionMultDiv(expression);

    printf("Result: %lf\n", result);

    FreeList(expression);
}


//Function to get the expression from user for add and sub
void ParseExpressionAddSub(void) 
{
CorrectExp:
    Node *expression = NULL;
    printf("Enter an arithmetic expression (using +, -): ");
    char inputChar;
    while ((inputChar = getchar()) != '\n' && inputChar != EOF) {
        Append(&expression, inputChar);
    }
    
        //This part of the code checks that the user did not mix between (+ or -)and(* or /)
        bool containsAdd = false;
        bool containsSub = false;
        bool containsMult = false;
        bool containsDiv = false;
        Node *temp = expression;
        while (temp != NULL) {
            if (temp->data == '+') 
            {
                containsAdd = true;
            }
            
            else if (temp->data == '-')
            {
                containsSub = true;
            }
            
            else if (temp->data == '*')
            {
                containsMult = true;
            }
            
            else if (temp->data == '/')
            {
                containsDiv = true;
            }
            
            temp = temp->next;
        }

        if (((containsAdd || containsSub) && (containsMult || containsDiv)) || containsMult == true || containsDiv == true) {
            printf("\nError: Operators * and / are not allowed here.\n\n");
            FreeList(expression);
            goto CorrectExp;
        }

    double result = ExpressionAddSub(expression);

    printf("Result: %lf\n", result);

    FreeList(expression);
}




// Function to parse and calculate the result of the expression with multiplication and division
double ExpressionMultDiv(Node *head) {
    double result = 1.0; // Initialize result to 1.0 for multiplication
    double currentNumber = 0.0;
    char operation = '*'; // Set initial operation to multiplication
    bool isFirst = true;
    bool isDecimal = false;
    double decimalFraction = 0.1;

    while (head != NULL) {
        char currentChar = head->data;

        if ((currentChar >= '0' && currentChar <= '9') || currentChar == '.') {
            if (currentChar == '.') {
                isDecimal = true;
                head = head->next;
                continue;
            }

            if (!isDecimal) {
                currentNumber = currentNumber * 10 + (currentChar - '0');
            } else {
                currentNumber += (currentChar - '0') * decimalFraction;
                decimalFraction *= 0.1;
            }
        } else if (currentChar == '*' || currentChar == '/') {
            if (!isFirst) {
                if (operation == '*') {
                    result *= currentNumber;
                } else {
                    if (currentNumber == 0.0 && operation == '/') {
                        printf("Error: Division by zero.\n");
                        return 0; // Return 0 to indicate division by zero error
                    }
                    result /= currentNumber;
                }
            }
            currentNumber = 0.0;
            operation = currentChar;
            isDecimal = false;
            decimalFraction = 0.1;
        }

        isFirst = false;
        head = head->next;
    }

    // Perform the last operation
    if (operation == '*') {
        result *= currentNumber;
    } else {
        if (currentNumber == 0.0 && operation == '/') {
            printf("Error: Division by zero.\n");
            return 0; // Return 0 to indicate division by zero error
        }
        result /= currentNumber;
    }

    return result;
}



// Function to parse and calculate the result of the expression
double ExpressionAddSub(Node *head) {
    double result = 0.0;
    double currentNumber = 0.0;
    int sign = 1; // Sign of the number (positive or negative)
    bool isDecimal = false;
    double decimalFraction = 0.1;

    while (head != NULL) {
        char currentChar = head->data;

        if ((currentChar >= '0' && currentChar <= '9') || currentChar == '.') {
            if (currentChar == '.') {
                isDecimal = true;
            } else {
                if (!isDecimal) {
                    currentNumber = currentNumber * 10 + (currentChar - '0');
                } else {
                    currentNumber += (currentChar - '0') * decimalFraction;
                    decimalFraction *= 0.1;
                }
            }
        } else if (currentChar == '+' || currentChar == '-') {
            result += sign * currentNumber;
            currentNumber = 0.0;
            sign = (currentChar == '+') ? 1 : -1;
            isDecimal = false;
            decimalFraction = 0.1;
        }

        head = head->next;
    }

    // Add the last number after the loop
    result += sign * currentNumber;

    return result;
}


void PrimeFact(void)
{
    unsigned int dividend;
    int divisor;
    double x;
    
    
    printf("Type in your (positive integer) number: ");
    scanf("%lf",&x);
    x = fabs(x);
    dividend = (unsigned int)x;
    
    divisor = 2;
    while (dividend > 1)
    {
        if (dividend % divisor == 0) 
        { /* if divisible */
            printf("%dx", divisor);
            dividend = dividend / divisor;
        }
        else
            divisor = divisor + 1;  /* not divisable */
    }
    printf("%d\n", 1);
    
    return;
    
}






//Main program !
int main(void) {
    
    
    CheckConfig();
  
    int choice = 0;
   
   do{
    printf("\n\nChoose a menu:\n  1.Basic Operations\n  2.Math Functions\n  3.Edit Settings\n  4.Conversions\n  5.Read Memory\n  0.Exit\n\n");
correct:
    scanf("%i",&choice);
    
    switch (choice)
    {
        case 1: ChooseOp();
            break;

        case 2: Choosefct();
            break;

        case 3: Edit();
            break;

        case 4: Convert();
            break;

        case 5: ReadMem();
            break;

        case 0: printf("\n\nExiting Calculator ... ");
            break;

        default: printf("Please choose a number from the list !");
            goto correct;
    }
   } while (choice != 6);

    return 0;
}



