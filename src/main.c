/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

#include <speex/speex.h>

char input_bytes[100];
short output_frame[100];

int main(void)
{
	SpeexBits bits;

	void *dec_state;

	speex_bits_init(&bits);

	dec_state = speex_decoder_init(&speex_wb_mode);

	int frame_size;
	speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &frame_size);

	int enh = 0;
	speex_decoder_ctl(dec_state, SPEEX_SET_ENH, &enh);

	int wbBytes = 100;
	speex_bits_read_from(&bits, input_bytes, wbBytes);

	speex_decode_int(dec_state, &bits, output_frame);

	speex_bits_destroy(&bits);
	speex_decoder_destroy(dec_state);

	for(;;);
}
