# LEDSignalPatterns
This code was created for a custom made LED shirt called WEARABLE BEACON. You can find more about this shirt at http://martyf1y.tumblr.com/ or https://vimeo.com/132664622

It was designed specifically for the amount of rows and columns of the shirt but can be changed by altering the array: 
int LEDsArray[] = {24,25,26,27,38,40,40,40,40,37,36,35,35,34,34,34,34,34,35,35,36,37,40,40,40,40,38,27,26,25,24};

The code is fairly simple. It uses the Adafruit library and is best to follow their instructions for working with LED strips and executing the code. I have modified their library by adding in three extra functions to get information about the RGB of the LEDs. Use the library given in the zip file to have my code work correctly, or just declare and add the functions to their code. They are:

    getRedColor(uint16_t n) const,
    getGreenColor(uint16_t n) const,
    getBlueColor(uint16_t n) const;

The code so far has only been able to work with the Arduino Mega. This is because it uses more than 2.5kb of SRAM. 

If you have any concerns with the code or ways to make it better please email me at martyfly.ta@gmail.com. I would also like to see pictures! :)


