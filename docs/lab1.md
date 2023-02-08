# Use Vivado to build an Embedded System

## Objectives

After completing this lab, you will be able to:
*	Create a Vivado project for a Zynq system.
*	Use the IP Integrator to create a hardware system.
*	Use Vitis IDE to create a standard memory test project.
*	Run the test application on the board and hence verify hardware functionality.

## Steps
### Create a Vivado Project

1.	Open Vivado by selecting **Start > All Programs > Xilinx Design Tools > Vivado 2021.2**
1.	Click **Create Project** to start the wizard. You will see the Create a New Vivado Project dialog box. Click Next.
1.	Click the Browse button of the Project Location field of the New Project and browse to **{labs}**, and click Select.
1.	Enter **lab1** in the Project Name field.  Make sure that the **Create Project Subdirectory** box is checked.  Click Next.
1.	In the Project Type form select **RTL Project**, and check the box **Do not specify sources at this time**. Click **Next**
1.	In the Default Part window, select the Boards tab, and depending on the board you are using, (if you can't find the board you are looking for, refer to ![README.md](/README.md) for setup) and click Next.

    <p align="center">
    <img src ="pics/lab1/1_BoardsandParts.jpg" width="80%" height="80%"/>
    </p>
    <p align = "center">
    <i>Boards and Parts Selection</i>
    </p>

1.	Check the Project Summary (should be similar to what you see below) and click Finish to create an empty Vivado project.
    <p align="center">
    <img src ="pics/lab1/2_ProjectSummary.jpg" width="80%" height="80%"/>
    </p>
    <p align = "center">
    <i>Project Summary</i>
    </p>


### Creating the System Using the IP Integrator

1.	In the Flow Navigator, click **Create Block Design** under IP Integrator.
    <p align="center">
    <img src ="pics/lab1/3_CreateIP.jpg" width="20%" height="20%"/>
    </p>
    <p align = "center">
    <i>Create IP Integrator Block Diagram</i>
    </p>

1.	Enter **system** for the design name and click OK.

1.	Right-click anywhere in the Diagram workspace and select **Add IP**.
    <p align="center">
    <img src ="pics/lab1/4_AddIP.jpg" width="80%" height="80%"/>
    </p>
    <p align = "center">
    <i>Add IP to Block Diagram</i>
    </p>        


1.	Once the **IP Catalog** opens, type “zynq” into the Search bar, find and double click on **ZYNQ7 Processing System** entry, or click on the entry and hit the Enter key to add it to the design.

1.	Notice the message at the top of the Diagram window in a green label saying that Designer Assistance available. Click **Run Block Automation**.  

1.	A new window pops up called the Run Block Automation window. In it, select **/processing_system7_0**, leave the default settings and click OK.

1. Once Block Automation has been completed, notice that ports have been automatically added for the DDR (double data rate, a type of memory) and Fixed IO, and some additional ports are now visible. The imported configuration for the Zynq related to the board has been applied which will now be modified. The block should finally look like this:

    <p align="center">
    <img src ="pics/lab1/5_Zynqblck.jpg" width="90%" height="80%"/>
    </p>
    <p align = "center">
     <i> Zynq Block with DDR and Fixed IO ports</i>
    </p>  

1. Double-click on the added block to open the **Customization** window.
   Notice now the Customization window shows selected peripherals (with tick marks). This is the default configuration for the board applied by the block automation.

###	Configure the processing block with just UART 1 peripheral enabled.

1.	A block diagram of the Zynq should now be open again, showing various configurable blocks of the **Processing System**.

1. At this stage, the designer can click on various configurable blocks (highlighted in green) and change the system configuration.

1.	Click on one of the peripherals (in green) in the **Peripheral I/O Pins** block of the Zynq Block Design, or select the **MIO Configuration** tab on the left to open the configuration form

1.	Expand **Peripheral I/O Pins** if necessary, and ensure all the following I/O peripherals are deselected except UART 1.

    >**Note :** Select UART 0 for PYNQ-Z2 instead of UART 1


    i.e. Remove: &nbsp; <i>ENET

    &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; USB 0

    &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; SD 0

    &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Expand **GPIO** to deselect GPIO MIO

    &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Expand **Memory Interfaces** to deselect Quad SPI Flash

    &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Expand **Application Processor Unit** to disable Timer 0.
    </i>

    <p align="center">
    <img src ="pics/lab1/6_UART.jpg" width="90%" height="80%"/>
    </p>
    <p align = "center">
    <i> Selecting only UART 1</i>
    </p>  


1.	Select the **PS-PL Configuration** tab on the left.

1.	Expand **AXI Non Secure Enablement > GP Master AXI interface** and deselect M AXI GP0 interface.

1.	Expand **General > Enable Clock Resets** and deselect the FCLK_RESET0_N option.

1.	Select the **Clock Configuration** tab on the left. Expand the PL Fabric Clocks and deselect the FCLK_CLK0 option and click OK.

1. Click on the **Regenerate Layout button** (green arrow) shown below:
    <p align="center">
    <img src ="pics/lab1/7_RegValid.jpg" width="90%" height="80%"/>
    </p>
    <p align = "center">
    <i> Regenerating and Validating Design</i>
    </p>  

1.	Click on the **Validate Design button** (purple arrow) and make sure that there are no errors.

### Generate Top-Level and Export hardware

1.	In the sources panel, right-click on **system.bd**, and select **Generate Output Products…** and click Generate to generate the Implementation, Simulation and Synthesis files for the design (You can also click on **Generate Block Design** in the Flow Navigator pane to do the same).
    <p align="center">
    <img src ="pics/lab1/8_OP.jpg" width="40%" height="80%"/>
    </p>
    <p align = "center">
    <i> Generating output products </i>
    </p>  

1. Right-click again on system.bd, and select Create **HDL Wrapper…** to generate the top-level VHDL model. Leave the **Let Vivado manager wrapper** and **auto-update** option selected, and click OK.

    The system_wrapper.v file will be created and added to the project.  Double-click on the file to see the content in the Auxiliary pane.
    <p align="center">
    <img src ="pics/lab1/9_wrap.jpg" width="40%" height="80%"/>
    </p>
    <p align = "center">
    <i> The HDL Wrapper file generated and added to the project </i>
    </p>  

1. Notice that the Verilog file is already set as the top module in the design, indicated by the icon.
1. Select **File > Export > Export hardware** and click OK. (Save the project if prompted)
Note:  Since we do not have any hardware in Programmable Logic (PL) there is no bitstream to generate, hence the Include bitstream option is not necessary at this time.

1. Basic information about the hardware configuration of the project can be found in the Xilinx Support Archive (XSA) file, along with the Address maps for the PS systems, and driver information. The .xsa file is used in the software environment to determine the peripherals available in the system, and their location in the address map.
 
### Generate Memory Test Application in Vitis IDE

1. Select **Tools > Launch Vitis IDE**, and Select the workspace location with any given location path. Click Launch. The Vitis IDE opens.
1. Review the Welcome page and close it. Click **Create Application Project**, and click Next.
1. In the Platform Selection window, select **Create a new platform from hardware (XSA)** and browse to select the system_wrapper.xsa file exported before. (Default is in the {labs}\lab1 folder).
1. Enter **lab1_platform** as the _Platform name_, click **Next.**
    <p align="center">
    <img src ="pics/lab1/10_AddPlatform.jpg" width="80%" height="80%"/>
    </p>
    <p align = "center">
    <i> Select a platform to create the project </i>
    </p> 

1. In the project details window, name the project **lab1**, and in the Target Processor selection, select **ps7_cortexa9_0**.

1. Select **Memory Tests** as the template in the Template Selection window. Click **Finish**.
   <p align="center">
    <img src ="pics/lab1/12_SelTemplate.jpg" width="80%" height="80%"/>
    </p>
    <p align = "center">
    <i> Select a template to create the project </i>
    </p> 

1.	Expand folders in the Explorer view on the left, and observe that there are two projects – lab1_platform, and lab1_system.  The **lab1_system** project is the application that we will use to verify the functionality of the design.  The **lab1_platfrom** is a platform project includes the ps7_init function which initializes the PS as part of the first stage bootloader. The Explorer view should look something like this:
    <p align="center">
    <img src ="pics/lab1/13_Explorer.jpg" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i> The Project Explorer view </i>
    </p>  

1. Open the memorytest.c file in the **lab1_system > lab1 > src**, and examine the contents.  This file calls the functions to test the memory.

1. Build the application project either by clicking the hammer button or by right-clicking on the application project and selecting Build Project as shown in following figure. As the project builds, you can see the output in the Console window.
    <p align="center">
    <img src ="pics/lab1/14_Build.jpg" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i> Build the application project </i>
    </p>  

### Test in Hardware

1.	Make sure that micro-USB cable(s) is(are) connected between the board and the PC. Change the boot mode to JTAG. Turn ON the power of the board.
1. Open a serial communication utility for the COM port assigned on your system. The Vitis software platform provides a serial terminal utility will be used throughout the tutorial. You can also use your preferred serial terminal application.
   * To open this utility, select **Window > Show view**.
   * In the Show View dialog box, type **terminal** in the search box.
   * Select **Vitis Serial Terminal** and click **Open**.
    <p align="center">
    <img src ="pics/lab1/15_OpenVitisTerminal.jpg" width="35%" height="80%"/>
    </p>
    <p align = "center">
    <i> Open the Vitis Serial Terminal </i>
    </p>
 
1. Click the Add button in the Vitis Serial Terminal to connect to a serial terminal. Select the port from the dropdown menu. Keep the Advanced Settings as-is. Click OK.
   <p align="center">
    <img src ="pics/lab1/16_ConnectSerial.jpg" width="35%" height="80%"/>
    </p>
    <p align = "center">
    <i> Connect to serial port </i>
    </p>

1. Right-click **lab1_system > lab1** and select **Launch Hardware (Single Application Debug)**.
    <p align="center">
    <img src ="pics/lab1/17_OpenRunConfig.jpg" width="90%" height="80%"/>
    </p>
    <p align = "center">
    <i> Launch Run Configurations </i>
    </p>

1. You should see the following output on the Terminal tab.
    <p align="center">
    <img src ="pics/lab1/19_MemTestRun.jpg" width="60%" height="80%"/>
    </p>
    <p align = "center">
    <i> Connect to serial port </i>
    </p>

1. Close Vivado and Vitis IDE by selecting **File > Exit** in each program.

## Conclusion

Vivado and the IP Integrator allow base embedded processor systems and applications to be generated very quickly. After the system has been defined, the hardware can be exported and Vitis IDE can be invoked from Vivado.

Software development is done in Vitis IDE which provides several application templates including memory tests.  You verified the operation of the hardware by using a test application, executing on the processor, and observing the output in the serial terminal window.
