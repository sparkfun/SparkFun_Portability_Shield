---
icon: simple/arduino
---

###Example 1: Navigation Switch

This example demonstrates how to use the navigation switch and detect if the SD card is inserted. The !INT pin of the GPIO expander IC (PCA9554) triggers an interrupt any time a button is pressed or an SD card is inserted/removed.

The code for this example can be found in the [Firmware](../Firmware/Example1_NavigationSwitch/) folder of this repository. Alternatively, you can expand the link below and copy and paste the code into a shiny new Arduino sketch: 



One thing to note is that you will also need to install the SparkFun I2C Expander Arduino Library if you haven't already. You can click the link from within the code or you can download the zip from [the GitHub Repository](https://github.com/sparkfun/SparkFun_I2C_Expander_Arduino_Library/archive/refs/heads/main.zip)

<figure markdown>
[![SparkFun I2C Expander Arduino Library Install](assets/img/I2CExpanderLibraryInstall.png){ width="90%" }](assets/img/I2CExpanderLibraryInstall.png "Click to enlarge")
<figcaption markdown>SparkFun I2C Expander Arduino Library Install</figcaption>
</figure>


Make sure you've selected the correct board (in this case, we are using the RTK Postcard) and port in the Tools menu and then hit the upload button. Once the code has finished uploading, go ahead and open a [Serial Monitor](https://learn.sparkfun.com/tutorials/terminal-basics). You should see something similar to the following. 

<figure markdown>
[![Arduino Example 1 Output](assets/img/Example1_Output.jpg){ width="90%" }](assets/img/Example1_Output.jpg "Click to enlarge")
<figcaption markdown>Example 1 Output</figcaption>
</figure>


###Example 2: Fuel Gauge
This file demonstrates the simple API of the SparkFun MAX17043 Arduino library. 

The code for this example can be found in the [Firmware](../Firmware/Example2_FuelGauge/) folder of this repository. Alternatively, you can expand the link below and copy and paste the code into a shiny new Arduino sketch: 

One thing to note is that you will also need to install the SparkFun MAX1704x Fuel Gauge Arduino Library if you haven't already. You can click the link from within the code or you can download the zip from [the GitHub Repository](https://github.com/sparkfun/SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library/archive/refs/heads/main.zip)

<figure markdown>
[![SparkFun MAX1704x Fuel Gauge Arduino Library Install](assets/img/MAX17043LibraryInstall.png){ width="90%" }](assets/img/MAX17043LibraryInstall.png "Click to enlarge")
<figcaption markdown>SparkFun MAX1704x Fuel Gauge Arduino Library Install</figcaption>
</figure>


Make sure you've selected the correct board and port in the Tools menu and then hit the upload button. Once the code has finished uploading, go ahead and open a [Serial Monitor](https://learn.sparkfun.com/tutorials/terminal-basics) at 115200 baud. You should see the gauge's voltage and state-of-charge (SOC) readings, similar to the following: 

<figure markdown>
[![Arduino Example 2 Output](assets/img/Example2_Output.jpg){ width="90%" }](assets/img/Example2_Output.jpg "Click to enlarge")
<figcaption markdown>Example 2 Output</figcaption>
</figure>



###Example 3: Display

This example demonstrates how to display on the 1.3" OLED and read the fuel gauge. You should have the Portability Shield connected to the RTK Postcard or other controller. 

The code for this example can be found in the [Firmware](../Firmware/Example3_Display/) folder of this repository. Alternatively, you can expand the link below and copy and paste the code into a shiny new Arduino sketch: 




Make sure you've selected the correct board and port in the Tools menu and then hit the upload button. Once the code has finished uploading, you should see the gauge's voltage and state-of-charge (SOC) readings, similar to the following: 

<figure markdown>
[![Arduino Example 3 Output](assets/img/Example3_Output.jpg){ width="90%" }](assets/img/Example3_Output.jpg "Click to enlarge")
<figcaption markdown>Example 3 Output</figcaption>
</figure>




###Example 4: SD Card

This example will mount an SD card, analyze the type of card, and output the analysis via the Serial Monitor. 

Go ahead and connect the Portability Shield to the RTK Postcard or other controller board. Insert a microSD card into the socket. Cards up to 512GB should work.

The code for this example can be found in the [Firmware](../Firmware/Example4_SD/) folder of this repository. Alternatively, you can expand the link below and copy and paste the code into a shiny new Arduino sketch: 





Make sure you've selected the correct board and port in the Tools menu and then hit the upload button. Once the code has finished uploading, go ahead and open a [Serial Monitor](https://learn.sparkfun.com/tutorials/terminal-basics) at 115200 baud. 

<figure markdown>
[![Arduino Example 4 Output](assets/img/Example4_Output.jpg){ width="90%" }](assets/img/Example4_Output.jpg "Click to enlarge")
<figcaption markdown>Example 4 Output</figcaption>
</figure>
