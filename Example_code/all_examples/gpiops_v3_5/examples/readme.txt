/** \page example Examples
You can refer to the below stated example applications for more details on how to use gpiops driver.

@section ex1 xgpiops_intr_example.c
Contains an example on how to use the XGpiops driver directly.
This example shows the usage of the driver in interrupt mode.
and uses the interrupt capability of the GPIO to detect push button
events, set the output LEDs based on the input . The user needs to press
all the switches SW1-SW5 on the evaluation board to exit from this
example.

For details, see xgpiops_intr_example.c.

@section ex2 xgpiops_polled_example.c
Contains an example on how to use the XGpiops driver directly.
This example provides the usage of APIs for reading/writing to the
individual pins.Same example we are using in versal for execution of
pmc gpio.

@section ex3 xgpiops_polled_ps_example.c
Contains an example on how to use the XGpiops driver in versal ps gpio.
This example provides the usage of APIs for reading/writing to the
individual pins.


For details, see xgpiops_polled_example.c.
*/
