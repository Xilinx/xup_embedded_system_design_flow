# Adding Custom IP to the System

## Objectives

After completing this lab, you will be able to:
*	Use the IP Packager feature of Vivado to create a custom peripheral.  
*	Modify the functionality of the IP.
*	Add the custom peripheral to your design.
*	Add pin location constraints.
*	Add block memory to the system.


## Steps

### Create a Custom IP using the Create and Package IP Wizard

1.	Open Vivado by selecting **Start > All Programs > Xilinx Design Tools > Vivado 2021.2 > Vivado 2021.2**.
1.	Click **Manage IP** and select **New IP Location** and click Next in the New IP Location window.
1.	Click on the browse button for the Part section. Click on boards and select the PYNQ-Z2 as your part. Click OK.
1.	Select Verilog as the Target Language, Mixed as the Simulator language, and for IP location, type **{labs}\led_ip** and click Finish (leave other settings as defaults and click OK if prompted to create the directory)

     <p align="center">
     <img src ="pics/lab3/1_ipst.jpg" width="80%" height="80%"/> 
     </p>
     <p align = "center">
     <i>New IP Location form (**Needs to be Updated**)</i>
     </p>


###	Run the Create and Package IP Wizard

1.	Select **Tools > Create and Package New IP**.
2.	In the window, click Next.
3.	Select **Create a new AXI4 peripheral**, and click Next.
4.	Fill in the details for the IP.

    Name: *led_ip*

    Display Name: *led_ip_v1_0*

    (Fill in a description, Vendor Name, and URL)

5.	Click Next.
6.	Change the Name of the interface to **S_AXI**.
7.	Leave the other settings as default and click **Next** (*Lite interface, Slave mode, Data Width: 32, Number of Registers: 4*).

8.	Select **Edit IP** and click **Finish** (a new Vivado Project will open).

###	Create an interface to the LEDs

1.	In the sources panel, double-click the led_ip_v1_0.v file.

     This file contains the HDL code for the interface(s) selected above. The top level file contains a module which implements the AXI interfacing logic, and an example design to write to and read from the number of registers specified above. This template can be used as a basis for creating custom IP. A new parameterized output port to the LEDs will be created at the top level of the design, and the AXI write data in the sub-module will be connected back up to the external LED port.

     Scroll down to line 7 where a user parameters space is provided.  
2.	Add the line:

    ```verilog
    parameter integer LED_WIDTH = 8,
    ```

3.	Go to line 18 and add the line:

    ```verilog
    output wire [LED_WIDTH-1:0] LED,
    ```
    > don't forget to add commas when adding a port.

4.	Insert the following at line ~48:
    ```verilog
    .LED_WIDTH(LED_WIDTH),
    ```
5.	Insert the following at line ~52:
    ```verilog
    .LED(LED),
    ```


6.	Save the file by selecting **File > Save File**.
7.	Expand led_ip_v1_0 in the sources view if necessary, and open led_ip_v1_0_S_AXI.v.
8.	Add the LED parameter and port to this file too, at lines 7 and 18 (done in steps 2 ands 3).

9.	Scroll down to ~line 400 and insert the following code to instantiate the user logic for the LED IP.
(This code can be typed directly, or copied from the user_logic_instantiation.txt file in the lab3 source folder.)

    ```verilog
    lab3_user_logic  # (
        .LED_WIDTH(LED_WIDTH)
    )
    U1(
        .S_AXI_ACLK(S_AXI_ACLK),
        .slv_reg_wren(slv_reg_wren),
        .axi_awaddr(axi_awaddr[C_S_AXI_ADDR_WIDTH-1:ADDR_LSB]),
        .S_AXI_WDATA(S_AXI_WDATA),
        .S_AXI_ARESETN(S_AXI_ARESETN),
        .LED(LED)
    );
    ```
    Check all the signals that are being connected and where they originate.

10.	Save the file by selecting **File > Save File**.
11.	Click on the **Add Sources** in the Flow Navigator pane, select **Add or Create Design Sources**, click **Next**, then click the Plus icon then Add Files…, browse to **{sources}\lab3**, select the lab3_user_logic.v file and click OK, and then click **Finish** to add the file.

    Check the contents of this file to understand the logic that is being implemented.  Notice the formed hierarchy.

    > Make sure that when adding the source lab3_user_logic.v, untick the option: Copy sources into IP directory.

12.	Click **Run Synthesis** and **Save** if prompted. (This is to check the design synthesizes correctly before packaging the IP. If this was your own design, you would  simulate it and verify functionality before proceeding)
13.	Check the _Messages_ tab for any errors and correct if necessary before moving to the next step

    When Synthesis completes successfully, click Cancel.

###	Package the IP

1.	Click on the Package IP – led_ip tab

   <p align="center">
   <img src ="pics/lab3/2_PackIP.jpg" width="80%" height="80%"/>
   </p>
   <p align = "center">
   <i> Package IP</i>
   </p>

> Skip the next two steps (2 and 3) if you see /Basic_Elements under the Categories section, (like the one shown in figure)

1.	For the IP to appear in the IP catalog in particular categories, the IP must be configured to be part of those categories. To change which categories the IP will appear in the **IP catalog** click Blue Plus (Red box shown in the figure) in the **Categories** section. This opens the Choose IP Categories window
1.	For the purpose of this exercise, uncheck the **AXI Peripheral** box and check the **Basic Elements** and click OK.
1.	Select **Compatibility**. This shows the different Xilinx FPGA Families that the IP supports. The value is inherited from the device selected for the project during creating the IP.
1.	You should have something like this:
    <p align="center">
    <img src ="pics/lab3/3_ipfam.jpg" width="80%" height="80%"/>
    </p>
    <p align = "center">
    <i> Compatibility under Package IP</i>
    </p>
	>If this does not match up with what you have, click the blue plus then **Add Family Explicitly…** from the menu. Select the **Zynq family** (This is the family of devices the PYNQ-Z2 belongs to) and click OK.
1.	You can also customize the address space and add memory address space using the **Addressing and Memory** category.  We won’t make any changes this time.
1.	Click on **File Groups** and click **Merge changes** from File Groups Wizard.

    <p align="center">
    <img src ="pics/lab3/4_ipfile.jpg" width="70%" height="80%"/>
    </p>
    <p align = "center">
    <i> Compatibility under Package IP</i>
    </p>

    This is to update the IP Packager with the changes that were made to the IP and the lab3_user_logic.v file that was added to the project. Expand Verilog Synthesis and notice lab3_user_logic.v has been included.

1.	Click on **Customization Parameters** and again Merge changes from Customization Parameters Wizard.
Notice that the Ports and Interfaces view now shows the user created LED port
1.	Select **Customization Parameters**, expand **Hidden Parameters**, right-click on **LED_WIDTH**, and select **Import IP Parameters…** and click OK.
1.	Select **Customization GUI** and notice that the Led Width is visible.

    <p align="center">
    <img src ="pics/lab3/5_ipcustomzn.jpg" width="75%" height="80%"/>
    </p>
    <p align = "center">
    <i> Customization GUI under Package IP</i>
    </p>

1.	Select Review and Package, and notice the path where the IP will be created.
1.	Click **Re-Package IP**. Click Yes and the project will close when complete.
1.	In the original Vivado window click **File > Close Project**.

### Fix bugs for Windows
>You may encounter errors in later labs if you are using a Windows machine.

1. Browse to open the file **{labs}\led_ip\ip_repo\led_ip_1.0\drivers\led_ip_v1_0\src\Makefile**
1. Change line 12 ~ 14 to
    ```
    INCLUDEFILES=led_ip.h
    LIBSOURCES=led_ip.c led_ip_selftest.c
    OUTS=led_ip.o led_ip_selftest.o
    ```
1. Save and close the file

### Modify the Project Settings

1.	Start the Vivado if necessary and open the lab2 project you created in the previous lab.
2.	Select **File > Project > Save As…** to open the Save Project As dialog box. Enter **lab3** as the project name.  Make sure that the **Create Project Subdirector**y option is checked, the project directory path is **{labs}** and click OK.
3.	Click **Settings** in the Flow Navigator pane.
4.	Select **IP > Repository** in the left pane of the Project Settings form.
5.	Click on the Blue Plus button, browse to **{labs}\led_ip** and click Select. The led_ip_v1.0 IP will appear the IP in the Selected Repository window.
    <p align="center">
    <img src ="pics/lab3/6_chooseip.jpg" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i> Specify IP Repository </i>
    </p>

6.	Click OK, Click Apply, and Click OK.

### Add the Custom IP, BRAM, and the Constraints

1.	Click **Open Block Design** under IP Integrator in the Flow Navigator pane
1.	Right Click on the Diagram window and **Add IP..**. Search for **led_ip_v1.0** in the catalog by typing "led" in the search field.
1.	Double-click **led_ip_v1_0** to add the core to the design.
1.	Select the IP in the block diagram and change the instance name to **led_ip** in the properties view.
1.	Double click the block to open the configuration properties
1.	For the _PYNQ-Z2_, set the width to **4**.
1.	Click OK.
1.	Click on Run Connection Automation, select **/led_ip/S_AXI** and click OK to automatically make the connection from the AXI Interconnect to the IP.
1.	Select the LED port on the led_ip instance (by clicking on its pin), right-click and select **Make External**. Rename the port as **LED**.

    <p align="center">
    <img src ="pics/lab3/7_LEDext.jpg" width="70%" height="80%"/>
    </p>
    <p align = "center">
    <i> LED external port added and connected </i>
    </p>


1.	Select the **Address Editor** tab and verify that an address has been assigned to led_ip.

1.	In the Block Diagram, Right click and select the Add IP option. Search for _BRAM_ and add one instance of the **AXI BRAM Controller**
1.	Run Connection Automation on **axi_bram_ctrl_0/S_AXI** and click OK when prompted to connect it to the M_AXI_GP0 Master.
1.	Double click on the block to customize it and change the **number of BRAM interfaces** to 1 and click OK.
Notice that the AXI Protocol being used is **AXI4** instead of AXI4Lite since BRAM can provide higher bandwidth and the controller can support burst transactions.
1.	Click on **Run Connection Automation** to add and connect a Block Memory Generator by selecting **axi_bram_ctrl_0/BRAM_PORTA** and click OK (This could be added manually)
1. Validate the design (**F6**) to ensure there are no errors , and click the regenerate button to redraw the diagram.
The design should look similar to the figure below.

  <p align="center">
  <img src ="pics/lab3/8_Completeblck.jpg" width="90%" height="80%"/>
  </p>
  <p align = "center">
  <i> Completed Block Diagram </i>
  </p>

1.	In the Address editor, notice the Range of the _axibramctrl_0_ is 8K. We will leave it at that.
1.	Press **F6** to validate the design one last time.

1.	Click **Add Sources** in the Flow Navigator pane, select **Add or Create Constraints**, and click Next.
1.	Click the Blue Plus button, and then **Add Files…**, browse to the **{sources}\lab3** folder, select lab3_pynq_z2.xdc for _PYNQ-Z2_.
1.	Click **Finish** to add the file.
1.	Expand Constraints folder in the Sources pane, and double click the **lab3_*.xdc** file entry to see its content. This file contains the pin locations and IO standards for the LEDs on the _Zynq_ board. This information can usually be found in the manufacturer’s datasheet for the board.
1.	Right click on system.bd and select **Generate output products**
1.	Click on **Generate Bitstream** and click Yes if prompted to save the Block Diagram, and click Yes again if prompted to launch **Synthesis** and **Implementation**. Click Cancel when prompted to Open the Implemented Design

## Conclusion

Vivado IP packager was used to import a custom IP block into the IP library. The IP block was then added to the system. Connection automation was run where available to speed up the design of the system by allowing Vivado to automatically make connections between IP. An additional BRAM was added to the design. Finally, pin location constraints were added to the design. This lab is build upon and tested in Lab 4.


------------------------------------------------------
<p align="center">Copyright&copy; 2022, Advanced Micro Devices, Inc.</p>