/*
 *  Program:  encryptor
 *  Author:   Chris Brewer
 *  Date:     10/30/2013
 *
 *  Function: This program takes a text file and encrypts it by incrementing the
 *            ASCII values of each character in the file by +1.  To decrypt a file,
 *            all the ASCII values of the characters in the encrypted file are
 *            decremented by 1.
 *            Obviously this is not a method to do any serious encryption with, and you can
 *            reverse the functions (tell it to decrypt first and it will be 'encrypted' and
 *            encrypt the file to 'decrypt' it) to get the same result.
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

/* Function to get create the output file name based off of the input file name.
 * If the filename being encrypted/decrypted has a 'e_' or 'd_' as a prefix,
 * it will be stripped off so the appropriate prefix can be added to the output file name.
 * @param: string file - the name of the file
 * @param: int edFlag - the flag indicating whether encryping (1) or decrypting (-1);
 */
string getOutFileName(string file, int edFlag){
    // remove the 'e_' or 'd_' file prefixes if they exist from the original filename string
    string outFile = file;
    if(file.substr(0,2) == "e_" || file.substr(0,2) == "d_"){
        outFile = outFile.substr(2, outFile.length());
    }

    // add the appropriate prefix whether encrypting or decrypting
    if (edFlag == 1){
        outFile = "e_" + outFile;
    }
    else if (edFlag == -1) {
        outFile = "d_" + outFile;
    }
    else {
        cerr << "error reading encryption flag" << endl;
        exit(-1);
    }
    return outFile;
}

/*  Function to encrypt/decrypt based on the flag value passed in
 *  If encrypting, then all characters in the text file are changed to their acsii value +1
 *  If decrypting, then all characters in the text file are changed to their acsii value -1
 * @param: string file - the name of the file
 * @param: int edFlag - the flag indicating whether encryping (1) or decrypting (-1);
 */
void encrypt_decrypt(string file, int edFlag){
    string output = "";
    char ch;

    // Open the file, and modify each character as it is read in
    fstream fin(file, fstream::in);
    if (fin) {
        while(fin >> noskipws >> ch){
            /* change the value of the character just
             * read to its ascii value, increment by one,
             * then change back to a character */
            output += (char) ( ((int) ch) + edFlag);
        }
        fin.close();
    }
    else {
        cerr << "Error: unable to open file; make sure the file is not in use" << endl;
        exit(-1);
    }

    // Open a file for output and write the modified characters to it
    string outFile = getOutFileName(file, edFlag);
    fstream fout(outFile, fstream::out);
    if (fout) {
        fout << output;
        fout.close();
    }
    else {
        cerr << "Error: unable to open file; make sure the file is not in use" << endl;
        exit(-1);
    }
}

/* Function to print out the usage of the program and terminate in the event
 * there is a problem with the
 * type of file, or the argument received from the command line.
 */
void printUsageAndTerminate(){
    cerr << "Usage: encryptor <filename> <argument>" << endl;
    cerr << "Arguments:  -e encrypt, -d decrypt" << endl;
    cerr << "Example:  encryptor somefile.txt -d" << endl;
    exit(-1);
}

/* Function to validate the input received from the command line.
 * Checks both the file name received and the value of the argument
 * @param: string nameOfFile the name of the file being worked with
 * @param: string argument the argument received from the command line; expecting -d or -e
 * @return: if nameOfFile is a .txt file and -e or -d was received, then return true.
 *          otherwise return false
 */
bool validInput(string nameOfFile, string argument) {
    // Check to make sure the argument received is either -d or -e
    if (argument != "-d" && argument != "-e") {
        cerr << "Invalid argument: " << argument << endl;
        return false;
    }
    // Check to make sure the filename received is a .txt file
    if (nameOfFile.substr(nameOfFile.length()-4, nameOfFile.length()) != ".txt") {
        cerr << "Invalid file type: " << nameOfFile << " - please use .txt files" << endl;
        return false;
    }
    return true;
}

/*The main entry point of the program; this is where execution begins.*/
int main(int argc, char* argv[]){

    // Check to make sure the correct number of arguments were received from the command line
    if (argc < 3) {
        printUsageAndTerminate();
    }

    // Assign the arguments to string variables
    string filename = argv[1];
    string arg = argv[2];

    // Validate input
    if (!validInput(filename, arg)){
        printUsageAndTerminate();
    }

    // Encrypt or Decrypt based on argument received
    if (arg == "-e"){
        encrypt_decrypt(filename, 1);
    }
    else if (arg == "-d"){
        encrypt_decrypt(filename, -1);
    }
    else{
        cerr << "Argument passed validation when it shouldn't" << endl;
        exit(-1);
    }

    cout << "done";
    return 0;
}
