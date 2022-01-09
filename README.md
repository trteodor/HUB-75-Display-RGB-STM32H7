# RGB HUB-75 Display
In this project, I was controlling an RGB display with a standard HUB75 connector. 
Below is link to the video where I presents this project. Unfortunately, I am not satisfied with the quality of the MCU Source Code.

It's very old project now i only update, and refactor a bit MCU Source Code :) ( Jan - 2022 ) 

	When i was writing this code i wasn't know Well C language.
	
However, I got in there to present a little bit of this design. I speak Polish on the video:

* https://www.youtube.com/watch?v=K93QytEEgGw



![photo](https://github.com/trteodor/HUB-75-Display-RGB-STM32H7/blob/master/Pictures/266770409_446580937089154_2001470405314787855_n.jpg)

![photo256cPal](https://github.com/trteodor/HUB-75-Display-RGB-STM32H7/blob/master/Pictures/256ColorPalleteInScreen.png)

# Used Tools and references:
* https://lvgl.io/tools/imageconverter 
	* Used to convert images (16 indexed and True Color for 255 Color Bit Map )
* https://msalamon.pl/jak-przygotowac-obraz-dla-wyswietlacza-lcd-lub-tft/
* https://github.com/makerbase-mks/Software/tree/master/Image2LCD
	* Also used to convert images in C array
* https://forbot.pl/forum/topic/19492-sterownik-matryc-ledowych-z-interfejsem-hub75-na-stm32f730/
* http://www.batsocks.co.uk/readme/art_bcm_3.htm
	* Used to obtain 255 Color resolution
* https://tiny.pl/955g3
	* Here you can order example HUB-75 Display 32x32

