#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000L  // ������ ������� ����������

#define LED_COUNT 8  // ���������� �����������
#define BUTTON_PIN PINA0  // ����� ����, � �������� ���������� ������

#define set_bit(reg, bit) reg |= (1<<bit)  // ������ ��� ��������� ���� � ��������
#define clear_bit(reg, bit) reg &= ~(1<<bit)  // ������ ��� ������ ���� � ��������
#define toggle_bit(reg, bit) reg ^= (1<<bit)  // ������ ��� �������������� ���� � ��������

int main(void)
{
	DDRD = 0xFF;  // ������������� ���� D �� �����
	DDRA &= ~(1<<BUTTON_PIN);  // ������������� ��� ������ �� ����
	PORTA |= (1<<BUTTON_PIN); // �������� ������������� �������� �� ���� ������

	uint8_t led_mask = 0;  // ����� ��� ���������� ���������� �����������

	while(1)
	{
		if(bit_is_clear(PINA, BUTTON_PIN))  // ���� ������ ������
		{
			// ����������� ��������� ����������� �� ���������������
			toggle_bit(PORTD, led_mask);
			_delay_ms(50); // �������� ��� ���������� �������� ��������� ������
		}
		else  // ���� ������ �� ������
		{
			// ������ ������������ �� �������
			for(uint8_t i = 0; i < LED_COUNT; i++)
			{
				led_mask = (1<<i);  // ������������� ��� � �����
				PORTD = led_mask;  // ������� ����� �� ���� D
				_delay_ms(500);  // �������� ����� �������������� �����������
			}
		}
	}

	return 0;
}
