#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000L  // задаем частоту процессора

#define LED_COUNT 8  // количество светодиодов
#define BUTTON_PIN PINA0  // номер пина, к которому подключена кнопка

#define set_bit(reg, bit) reg |= (1<<bit)  // макрос для установки бита в регистре
#define clear_bit(reg, bit) reg &= ~(1<<bit)  // макрос для сброса бита в регистре
#define toggle_bit(reg, bit) reg ^= (1<<bit)  // макрос для инвертирования бита в регистре

int main(void)
{
	DDRD = 0xFF;  // устанавливаем порт D на выход
	DDRA &= ~(1<<BUTTON_PIN);  // устанавливаем пин кнопки на вход
	PORTA |= (1<<BUTTON_PIN); // включаем подтягивающий резистор на пине кнопки

	uint8_t led_mask = 0;  // маска для управления состоянием светодиодов

	while(1)
	{
		if(bit_is_clear(PINA, BUTTON_PIN))  // если кнопка нажата
		{
			// переключаем состояние светодиодов на противоположное
			toggle_bit(PORTD, led_mask);
			_delay_ms(50); // задержка для подавления дребезга контактов кнопки
		}
		else  // если кнопка не нажата
		{
			// мигаем светодиодами по очереди
			for(uint8_t i = 0; i < LED_COUNT; i++)
			{
				led_mask = (1<<i);  // устанавливаем бит в маске
				PORTD = led_mask;  // выводим маску на порт D
				_delay_ms(500);  // задержка между переключениями светодиодов
			}
		}
	}

	return 0;
}
