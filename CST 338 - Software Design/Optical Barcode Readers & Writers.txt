/**
 * CST 338 - Software Design - Assig4
 * Optical Barcode Readers and Writers:
 * This program uses the classes BarcodeImage and DataMatrix and an
 * interface BarcodeIO to decode and code barcodes.
 * Warren Ngoun
 * Yukio Rivera
 * Luis Jimenez
 * Jennah Yasin
 */
public class Assig4 {
    public static void main(String[] args) {

        String[] sImageIn =
        {
            "                                               ",
            "                                               ",
            "                                               ",
            "     * * * * * * * * * * * * * * * * * * * * * ",
            "     *                                       * ",
            "     ****** **** ****** ******* ** *** *****   ",
            "     *     *    ****************************** ",
            "     * **    * *        **  *    * * *   *     ",
            "     *   *    *  *****    *   * *   *  **  *** ",
            "     *  **     * *** **   **  *    **  ***  *  ",
            "     ***  * **   **  *   ****    *  *  ** * ** ",
            "     *****  ***  *  * *   ** ** **  *   * *    ",
            "     ***************************************** ",
            "                                               ",
            "                                               ",
            "                                               "

      };

    String[] sImageIn_2 =
      {
            "                                          ",
            "                                          ",
            "* * * * * * * * * * * * * * * * * * *     ",
            "*                                    *    ",
            "**** *** **   ***** ****   *********      ",
            "* ************ ************ **********    ",
            "** *      *    *  * * *         * *       ",
            "***   *  *           * **    *      **    ",
            "* ** * *  *   * * * **  *   ***   ***     ",
            "* *           **    *****  *   **   **    ",
            "****  *  * *  * **  ** *   ** *  * *      ",
            "**************************************    ",
            "                                          ",
            "                                          ",
            "                                          ",
            "                                          "

      };


      BarcodeImage bc = new BarcodeImage(sImageIn);
      DataMatrix dm = new DataMatrix(bc);

      //first secret message
      System.out.println();
      dm.translateImageToText();
      dm.displayTextToConsole();
      dm.displayImageToConsole();
      
      //second secret message
      System.out.println();
      bc = new BarcodeImage(sImageIn_2);
      dm.scan(bc);
      dm.translateImageToText();
      dm.displayTextToConsole();
      dm.displayImageToConsole();

      //create your own message
      System.out.println();
      dm.readText("What a great resume builder this is!");
      dm.generateImageFromText();
      dm.displayTextToConsole();
      dm.displayImageToConsole();
    }
}

// This class will realize essential data and methods associated with a 
// 2D pattern, thought conceptually as an image of square or rectangular
// bar code.
class BarcodeImage implements Cloneable {
    public static final int MAX_HEIGHT = 30; // number of ROWS
    public static final int MAX_WIDTH = 65; // number of COLUMNS
    // Our image will be represented as a 2D array of BOOLEANS
    private boolean[][] imageData; 

    // Default constructor
    public BarcodeImage() {
        // First create a 2D array of correct sizing
        // HOW TO THINK ABOUT IT: imageData[NUM of ROWS][NUM of COLS]
        this.imageData = new boolean[MAX_HEIGHT][MAX_WIDTH];
        // Then loop through each member and fill it w FALSE
        for (int X = 0; X < MAX_WIDTH; X++) {
            for (int Y = 0; Y < MAX_HEIGHT; Y++) {
                this.imageData[Y][X] = false;
            }
        }
    }

    // Explicit constructor
    public BarcodeImage(String[] strData) {
        int yTracker;
        int xTracker;
        this.imageData = new boolean[MAX_HEIGHT][MAX_WIDTH];
        // Then loop through each member and fill it w FALSE
        for (int X = 0; X < MAX_WIDTH; X++) {
            for (int Y = 0; Y < MAX_HEIGHT; Y++) {
                this.imageData[Y][X] = false;
            }
        }

        // Check if we're w/in the size limits of MAX_WIDTH. 
        // Assumes input strings will all be the same length.
        if (checkSize(strData)) {
            // Use trackers to keep track of target coordinates.
            yTracker = 29;
            xTracker = 0;

            // Iterates through the strData arr in reverse.
            for (int oldY = strData.length - 1;
            oldY >= 0; oldY--) { 
                // Iterates through the individual strings of strArr
                for (int oldX = 0; oldX < strData[oldY].length() - 1; oldX++) { 
                    if (strData[oldY].charAt(oldX) == '*') {
                        this.imageData[yTracker][xTracker] = true;
                    } else {
                        this.imageData[yTracker][xTracker] = false;
                    }
                    xTracker++;
                }
                xTracker = 0;
                yTracker--;
            }
        }
    }

    /**
     * getPixel: Accessor for each bit in the image
     *
     * @param row the ROW or the Y coordinate to grab
     * @param col the COl or the X coordinate to grab
     * @return returns a boolean representing the pixel
     */
    public boolean getPixel(int row, int col) {
        // Checks if values of row & col are valid first
        if (row >= 0 && row < MAX_HEIGHT && col >= 0 && col < MAX_WIDTH) {
            return this.imageData[row][col];
        }
        return false;
    }

    /**
     * setPixel: mutator for each bit in the image
     *
     * @param row the ROW or the Y coordinate to grab
     * @param col the COL or the X coordinate to grab
     * @param value the boolean value to SET the pixel to
     * @return True if the operation was legal, False if out of bounds
     */
    public boolean setPixel(int row, int col, boolean value) {
        // Checks if row & col are valid
        if (row >= 0 && row < MAX_HEIGHT && col >= 0 && col < MAX_WIDTH) {
            return this.imageData[row][col] = value;
        }
        return false;
    }

    /**
     * checkSize: checks the incoming data for every conceivable
     * size or null error.
     * 
     * @param data the input 1D array of strings to process
     * @return True if the sizes are correct/strings aren't null.
     * False if any of those params are invalid.
     */
    private boolean checkSize(String[] data) {
        if (data == null) {
            return false;
        }
        for (String each : data) {
            // Ensures each incoming string will be at MAX 64 long.
            if (each.length() > MAX_WIDTH) {
                return false;
            }
        }
        return true;
    }

    /**
     * displayToConsole: Prints the ENTIRE BarcodeImage out w/ tons of 
     * whitespace to see the whole image for debugging purposes.
     */
    public void displayToConsole() {
        int dash;
        // Prints by going down each row one at a time
        for(dash = MAX_WIDTH + 2; dash > 0; dash--) {
            System.out.print("-");
        }
        System.out.println();
        // Loops through the ROWs and adds a line for the side borders
        for (int Y = 0; Y < MAX_HEIGHT; Y++) {
            System.out.print("|");
            for (int X = 0; X < MAX_WIDTH; X++) {
                if(this.imageData[Y][X] == true){
                    System.out.print(DataMatrix.BLACK_CHAR);
                } else {
                    System.out.print(DataMatrix.WHITE_CHAR);
                }
            }
            System.out.print("|");
            System.out.println();
        }
        for (dash = 0; dash < MAX_WIDTH + 2; dash++) {
            System.out.print("-");
        }
        System.out.println();
    }

    /**
     * clone: Clones the barcode image.
     *
     * @return the Object that has been cloned
     * @throws CloneNotSupportedException if the object doesn't clone
     */
    public Object clone() throws CloneNotSupportedException {
        // Blank image
        BarcodeImage toClone = new BarcodeImage();
        // Clones by using MAX values to loop
        for (int Y = 0; Y < MAX_HEIGHT; Y++) {
            for (int X = 0; X < MAX_WIDTH; X++) {
                toClone.setPixel(Y, X, this.getPixel(Y, X));
            }
        }
        return toClone;
    }
}

// The class that will contain both a BarcodeImage member object and a
// text String that represents the message encoded in the embedded image.
class DataMatrix implements BarcodeIO {
    public static final char BLACK_CHAR = '*';
    public static final char WHITE_CHAR = ' ';

    private BarcodeImage image;
    private String text;
    private int actualWidth;
    private int actualHeight;

    // Default Constructor
    public DataMatrix() {
        this.image = new BarcodeImage();
        this.text = "undefined";
        this.actualHeight = 0;
        this.actualWidth = 0;
    }
    
    // Explicit Constructors
    public DataMatrix(BarcodeImage image) {
        // Sets internal image
        this.image = new BarcodeImage();
        // Calls scan() to avoid duplication of code
        scan(image);
    }

    public DataMatrix(String text) {
        // Sets internal text
        this.text = text;
        // Calls readText() to avoid duplication of code
        this.readText(text);
    }

    /**
     * readText: Mutator for text.
     *
     * @param text our external text to use to modify our internal
     * @return True if the operation was successful. False if text was null.
     */
    public boolean readText(String text) {
        if (text != null) {
            this.text = text;
            return true;
        } else {
            return false;
        }
    }

    /**
     * scan: Mutator for our internal image.
     *
     * @param image the image to copy/clone from.
     * @return True if the clone succeeded. False if it didn't.
     */
    public boolean scan(BarcodeImage image) {
        // Calls clone() and requires the catch of a
        // CloneNotSupportedException by using try/catch block
        try {
            this.image = (BarcodeImage)image.clone();
            this.cleanImage();
            this.actualWidth = this.computeSignalWidth();
            this.actualHeight = this.computeSignalHeight();
            return true;
        } catch (CloneNotSupportedException e) {
            return false;
        }
    }

    /**
     * getActualWidth : accessor for actualWidth
     * 
     * @return the store int width value of the internal image
     */
    public int getActualWidth() {
        return this.actualWidth;
    }

    /**
     * getActualHeight: accessor for actualHeight
     * 
     * @return the store int height value of the internal image
     */
    public int getActualHeight() {
        return this.actualHeight;
    }

    /**
     * computeSignalWidth: uses the "spine" to determine size of width.
     * Reads the bottom borderline and subtracts 2 for the L/R columns.
     * 
     * @return the int value of the size of the actual inner image
     */
    private int computeSignalWidth() {
        int widthTracker = 0;
        int rowTracker = 29;
        // Start on the Last Row & count the closed borderline
        for (int X = 0; X < BarcodeImage.MAX_WIDTH; X++) {
            if (this.image.getPixel(rowTracker, X)) {
                widthTracker++;
            }
        }
        return (widthTracker - 2);
    }

    /**
     * computeSignalHeight: uses the "spine" to determine size of height 
     * by reading the total - 2 (for the borderlines).
     * 
     * @return the int value of the height of the BarcodeImage
     */
    private int computeSignalHeight() {
        int heightTracker = 0;
        for (int Y = 0; Y < BarcodeImage.MAX_HEIGHT; Y++) {
            if (this.image.getPixel(Y, 0)) {
                heightTracker++;
            }
        }
        return (heightTracker - 2);
    }

    /**
     * generateImageFromText: Given valid text, function generates
     * a aligned BarcodeImage encoded using binary values for each 
     * char in the string.
     * 
     * @return True if operation successful. False if text null OR 
     * too large to fit in our MAX_WIDTH sized BarcodeImage.
     */
    public boolean generateImageFromText() {
        // checks if text is 63 chars long (63 is the max cause of the
        // borderlines) and if longer then won't generate anything.
        // checks the text value IS NOT null b/c can't use null text.
        if (text != null && text.length() < BarcodeImage.MAX_WIDTH - 2) {
            BarcodeImage newImage = new BarcodeImage(); // Fresh image
            char[] textChars = this.text.toCharArray(); // Turn text to chars
            int widthTracker = 1;
            // Iterates through each Char in the String
            for (int i = 0; i < textChars.length; i++) {
                // Create binary string rep. of char "01100110"
                String toPrint = 
                Integer.toBinaryString((int) textChars[i]).toString();
                String leadingZero = 
                String.format("%8s", toPrint).replace(' ', '0');
                // Use that binary string to create a COL of *s
                for (int Y = 0; Y < leadingZero.length(); Y++) {
                    if (leadingZero.charAt(Y) == '1') {
                        newImage.setPixel(Y + 21,
                        widthTracker, true);
                    }
                }
                widthTracker++;
            }

            widthTracker++; // Makes the LEFT & RIGHT Borderlines
            for (int Y = 20; Y < BarcodeImage.MAX_HEIGHT; Y++) {
                newImage.setPixel(Y, 0, true); // Solid Line
                if (Y % 2 != 0) { // Alternating pattern      
                    newImage.setPixel(Y, widthTracker - 1, true);
                }
            }
            // Makes the TOP & BOTTOM Borderlines
            for (int X = 0; X < widthTracker; X++) {
                newImage.setPixel(29, X, true); // Solid Line
                if (X % 2 == 0) { // Alternating pattern
                    newImage.setPixel(BarcodeImage.MAX_HEIGHT-10, X, true);
                }
            }
            this.image = newImage;
            this.actualHeight = computeSignalHeight();
            this.actualWidth = computeSignalWidth();
            return true;
        } else {
            return false;
        }
    }

    /**
     * translateImageToText: Runs through ALIGNED image and processes 
     * and converts the binary representation to a human readable string.
     * 
     * @return Returns TRUE if operation successful & there's new
     *  text set. Returns FALSE if there IS no image.
     */
    public boolean translateImageToText() {
        // IF there IS an image, then we translate to text. Otherwise 
        // we don't do anything and return false.
        if (this.image != null) {
            String newText = "";
            // loop runs from col 1 to one after the last element.
            for (int X = 1; X < computeSignalWidth() + 1; X++) {
                String tempBoolStr = "";
                // Sets tempY outside for (b/c its alr 80+ chars long).
                int altY = (BarcodeImage.MAX_HEIGHT 
                - 1) - computeSignalHeight();
                // Runs the loop by COLs & iterates the ROWS top to
                // bottom. Uses getPixel and If to build binary string.
                for (int Y = altY; Y < BarcodeImage.MAX_HEIGHT - 1; Y++) {
                    if (this.image.getPixel(Y, X) == true) {
                        tempBoolStr += "1";
                    } else {
                        tempBoolStr += "0";
                    }
                }
                // Parses binary string and converts to int, then
                // char. After it appends to our newText.
                newText += (char)Integer.parseInt(tempBoolStr, 2);
            }
            // Finally sets the text to the decoded string & returns.
            this.text = newText;
            return true;
        } else {
            return false;
        }
    }
    
    /**
     * displayTextToConsole: Simple I/O op to print the internal 
     * text through System.out.println()
     */
    public void displayTextToConsole() {
        System.out.println(text);
    }

    /**
     * displayImageToConsole: Loops through the BarcodeImage &
     * uses actualWidth/Height to determine the limits of the 
     * image so we can get rid of empty whitespace.
     */
    public void displayImageToConsole() {
        // Prints by going down each row one at a time
        // FIRST prints the TOP border in dashes
        for (int dash = actualWidth + 4; dash > 0; dash--) {
            System.out.print("-");
        }
        System.out.println();
        // Compute our limits outside the for (b/c of 80 char length).
        int limitY = BarcodeImage.MAX_HEIGHT - (actualHeight + 2);
        int limitX = (actualWidth + 2);
        // Then as we print each ROW add a side border line.
        // Uses limits to determine how far we iterate each loop.
        for (int Y = limitY; Y <= BarcodeImage.MAX_HEIGHT - 1; Y++) {
            System.out.print("|");
            for (int X = 0; X < limitX; X++) {
                if (this.image.getPixel(Y, X) == true) {
                    System.out.print(DataMatrix.BLACK_CHAR);
                } else {
                    System.out.print(DataMatrix.WHITE_CHAR);
                }
            }
            System.out.print("|");
            System.out.println();
        }
    }

    /**
    *   cleanImage: Aligns misaligned BarcodeImage by finding the "spine" and 
    *   shifting it to the bottom most L-hand corner.
    */
    public void cleanImage() {
        BarcodeImage newImg = new BarcodeImage();
        BarcodeImage savedImg = this.image;
        // Our outer loop looks in reverse by ROWs or Ys for the first *
        for (int Y = BarcodeImage.MAX_HEIGHT - 1; Y > 0; Y--) {
            // Our inner loop looks by COLs or X coord for the first *
            for (int X = 0; X < BarcodeImage.MAX_WIDTH - 1; X++) {
                // Once we find the first * we do all our work here.
                // Begins the process of swapping the current (misaligned)
                // image from savedImg with the newImg that we'll set.
                if (image.getPixel(Y, X)) {
                    int targetY = 29;
                    int targetX = 0;
                    // Inner loop uses target/new coords to track
                    // coordinates they're currently working on.
                    for (int newY = Y; newY >= 0; newY--) {
                        for (int newX = X; newX 
                        < BarcodeImage.MAX_WIDTH; newX++) {
                            newImg.setPixel(targetY, targetX, 
                            savedImg.getPixel(newY, newX));
                            targetX++;
                        }
                        targetX = 0;
                        targetY--;
                    }
                    // Stops the outer loop from running. 
                    // We only needed the one point for reference.
                    Y = 0;
                    X = BarcodeImage.MAX_WIDTH;
                }
            }
        }
        // Finally set our image to our new one.
        this.image = newImg;
    }
}

interface BarcodeIO {
    public boolean scan(BarcodeImage image);

    public boolean readText(String text); 

    public boolean generateImageFromText();

    public boolean translateImageToText();

    public void displayTextToConsole();

    public void displayImageToConsole();
}

/* ======================= RUN =======================

CSUMB CSIT online program is top notch.    
-------------------------------------------
|* * * * * * * * * * * * * * * * * * * * *|
|*                                       *|
|****** **** ****** ******* ** *** *****  |
|*     *    ******************************|
|* **    * *        **  *    * * *   *    |
|*   *    *  *****    *   * *   *  **  ***|
|*  **     * *** **   **  *    **  ***  * |
|***  * **   **  *   ****    *  *  ** * **|
|*****  ***  *  * *   ** ** **  *   * *   |
|*****************************************|

You did it!  Great work.  Celebrate.
----------------------------------------
|* * * * * * * * * * * * * * * * * * * |
|*                                    *|
|**** *** **   ***** ****   *********  |
|* ************ ************ **********|
|** *      *    *  * * *         * *   |
|***   *  *           * **    *      **|
|* ** * *  *   * * * **  *   ***   *** |
|* *           **    *****  *   **   **|
|****  *  * *  * **  ** *   ** *  * *  |
|**************************************|

What a great resume builder this is!
----------------------------------------
|* * * * * * * * * * * * * * * * * * * |
|*                                    *|
|***** * ***** ****** ******* **** **  |
|* ************************************|
|**  *    *  * * **    *    * *  *  *  |
|* *               *    **     **  *  *|
|**  *   * * *  * ***  * ***  *        |
|**      **    * *    *     *    *  * *|
|** *  * * **   *****  **  *    ** *** |
|**************************************|

========================================== */