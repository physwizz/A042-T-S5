#ifndef JADARD_SORTING_H
#define JADARD_SORTING_H

#include "jadard_common.h"
#include "jadard_module.h"

#define JD_RSLT_OUT_PATH "/data/tpdata/"
#define JD_RSLT_OUT_FILE "jd_sorting_result.txt"
#define JD_OUTPUT_BUFFER_SIZE 0x1000
static char *jd_g_file_path = NULL;
static char *jd_g_rslt_data = NULL;

static int JD_SORTING_ACTIVE_ITEM;
static int JD_READ_THRESHOLD_SIZE;
static int **jd_g_sorting_threshold = NULL;
static uint8_t *GET_RAWDATA = NULL;

/* ASCII number */
#define ASCII_LF         (0x0A)
#define ASCII_CR         (0x0D)
#define ASCII_COMMA	     (0x2C)
#define ACSII_SPACE	     (0x20)
#define ACSII_COLON	     (0x3A)

/* Sorting config */
#define JD_SkipRawData_Frame_Number      0
#define JD_SkipDiffData_Frame_Number     0
#define JD_GetRawData_Frame_Number       1
#define SORTING_LPWUG_CHECK              0

char *jd_action_item_name[] = {
	"0._Open_Check",
	"1._Short_Check",
	"2._NormalActive_SB_Dev",
	"3._NormalActive_Noise",
	"4._NormalIdle_RawData_Check",
	"5._NormalIdle_Noise",
	"6._LpwugActive_SB_Dev",
	"7._LpwugActive_Noise",
	"8._LpwugIdle_RawData_Check",
	"9._LpwugIdle_Noise",
};

enum JD_SORTING_ACTION_ITEM {
	JD_SORTING_SLEEP_IN = 0,
	JD_SORTING_SLEEP_OUT,
	JD_SORTING_OPEN_CHECK,
	JD_SORTING_SHORT_CHECK,
	JD_SORTING_NORMALACTIVE_SB_DEV,
	JD_SORTING_NORMALACTIVE_NOISE,
	JD_SORTING_NORMALIDLE_RAWDATA_CHECK,
	JD_SORTING_NORMALIDLE_NOISE,
	JD_SORTING_LPWUGACTIVE_SB_DEV,
	JD_SORTING_LPWUGACTIVE_NOISE,
	JD_SORTING_LPWUGIDLE_RAWDATA_CHECK,
	JD_SORTING_LPWUGIDLE_NOISE,
};

enum JD_SORTING_ERROR_STATUS {
	JD_SORTING_OK                           = 0,
	JD_SORTING_SLEEP_IN_ERR                 = 1,
	JD_SORTING_SLEEP_OUT_ERR                = 1 << 1,
	JD_SORTING_OPEN_CHECK_ERR               = 1 << 2,
	JD_SORTING_SHORT_CHECK_ERR              = 1 << 3,
	JD_SORTING_NORMALACTIVE_SB_DEV_ERR      = 1 << 4,
	JD_SORTING_NORMALACTIVE_NOISE_ERR       = 1 << 5,
	JD_SORTING_NORMALIDLE_RAWDATA_CHECK_ERR = 1 << 6,
	JD_SORTING_NORMALIDLE_NOISE_ERR         = 1 << 7,
	JD_SORTING_LPWUGACTIVE_SB_DEV_ERR       = 1 << 8,
	JD_SORTING_LPWUGACTIVE_NOISE_ERR        = 1 << 9,
	JD_SORTING_LPWUGIDLE_RAWDATA_CHECK_ERR  = 1 << 10,
	JD_SORTING_LPWUGIDLE_NOISE_ERR          = 1 << 11,
};

enum JD_MPAP_PW {
	JD_MPAP_PW_NORMAL_ACTIVE_hbyte = 0xFF,
	JD_MPAP_PW_NORMAL_ACTIVE_lbyte = 0xFF,
	// JD_MPAP_PW_MP_SORTING_START_hbyte = 0x01,
	// JD_MPAP_PW_MP_SORTING_START_lbyte = 0x01,
	JD_MPAP_PW_MP_SORTING_FINISH_hbyte = 0x03,
	JD_MPAP_PW_MP_SORTING_FINISH_lbyte = 0x01,
	JD_MPAP_PW_MP_SHORT_START_hbyte = 0x04,
	JD_MPAP_PW_MP_SHORT_START_lbyte = 0x01,
	JD_MPAP_PW_MP_SHORT_FINISH_hbyte = 0x06,
	JD_MPAP_PW_MP_SHORT_FINISH_lbyte = 0x01,
	JD_MPAP_PW_MP_OPEN_START_hbyte = 0x07,
	JD_MPAP_PW_MP_OPEN_START_lbyte = 0x01,
	JD_MPAP_PW_MP_OPEN_FINISH_hbyte = 0x09,
	JD_MPAP_PW_MP_OPEN_FINISH_lbyte = 0x01,
	JD_MPAP_PW_MP_NORMAL_ACTIVE_START_hbyte = 0x0A,
	JD_MPAP_PW_MP_NORMAL_ACTIVE_START_lbyte = 0x01,
	JD_MPAP_PW_MP_NORMAL_ACTIVE_FINISH_hbyte = 0x0C,
	JD_MPAP_PW_MP_NORMAL_ACTIVE_FINISH_lbyte = 0x01,
	JD_MPAP_PW_MP_NORMAL_IDLE_START_hbyte = 0x0D,
	JD_MPAP_PW_MP_NORMAL_IDLE_START_lbyte = 0x01,
	JD_MPAP_MP_NORMAL_IDLE_FINISH_hbyte = 0x0F,
	JD_MPAP_MP_NORMAL_IDLE_FINISH_lbyte = 0x01,
	JD_MPAP_MP_MP_NORMAL_ACTIVE_DIFF_START_hbyte = 0x11,
	JD_MPAP_MP_MP_NORMAL_ACTIVE_DIFF_START_lbyte = 0x01,
	JD_MPAP_PW_MP_NORMAL_ACTIVE_DIFF_FINISH_hbyte = 0x13,
	JD_MPAP_PW_MP_NORMAL_ACTIVE_DIFF_FINISH_lbyte = 0x01,
	JD_MPAP_PW_MP_NORMAL_IDLE_DIFF_START_hbyte = 0x14,
	JD_MPAP_PW_MP_NORMAL_IDLE_DIFF_START_lbyte = 0x01,
	JD_MPAP_PW_MP_NORMAL_IDLE_DIFF_FINISH_hbyte = 0x16,
	JD_MPAP_PW_MP_NORMAL_IDLE_DIFF_FINISH_lbyte = 0x01,
	JD_MPAP_PW_MP_LPWUG_ACTIVE_START_hbyte = 0x01,
	JD_MPAP_PW_MP_LPWUG_ACTIVE_START_lbyte = 0x02,
	JD_MPAP_PW_MP_LPWUG_ACTIVE_FINISH_hbyte = 0x03,
	JD_MPAP_PW_MP_LPWUG_ACTIVE_FINISH_lbyte = 0x02,
	JD_MPAP_PW_MP_LPWUG_IDLE_START_hbyte = 0x04,
	JD_MPAP_PW_MP_LPWUG_IDLE_START_lbyte = 0x02,
	JD_MPAP_PW_MP_LPWUG_IDLE_FINISH_hbyte = 0x06,
	JD_MPAP_PW_MP_LPWUG_IDLE_FINISH_lbyte = 0x02,
	JD_MPAP_PW_MP_LPWUG_ACTIVE_DIFF_START_hbyte = 0x07,
	JD_MPAP_PW_MP_LPWUG_ACTIVE_DIFF_START_lbyte = 0x02,
	JD_MPAP_PW_MP_LPWUG_ACTIVE_DIFF_FINISH_hbyte = 0x09,
	JD_MPAP_PW_MP_LPWUG_ACTIVE_DIFF_FINISH_lbyte = 0x02,
	JD_MPAP_PW_MP_LPWUG_IDLE_DIFF_START_hbyte = 0x0A,
	JD_MPAP_PW_MP_LPWUG_IDLE_DIFF_START_lbyte = 0x02,
	JD_MPAP_PW_MP_LPWUG_IDLE_DIFF_FINISH_hbyte = 0x0C,
	JD_MPAP_PW_MP_LPWUG_IDLE_DIFF_FINISH_lbyte = 0x02,
	// JD_MPAP_PW_MP_UltraLowPower_START_hbyte = 0x0D,
	// JD_MPAP_PW_MP_UltraLowPower_START_lbyte = 0x02,
	// JD_MPAP_PW_MP_UltraLowPower_FINISH_hbyte = 0x0F,
	// JD_MPAP_PW_MP_UltraLowPower_FINISH_lbyte = 0x02,
};

enum JD_LCD_STATUS {
	JD_LCD_STATUS_SLEEP_IN = 0,
	JD_LCD_STATUS_SLEEP_OUT,
	JD_LCD_STATUS_DISPLAY_OFF,
	JD_LCD_STATUS_DISPLAY_ON,
};

enum JD_PST_MP_Mode {
	JD_PST_MP_Mode_Null = 0,
	JD_PST_MP_Mode_Sorting,
	JD_PST_MP_Mode_MP_Normal_Active,
	JD_PST_MP_Mode_MP_Normal_Active_Diff,
	JD_PST_MP_Mode_MP_Normal_Idle,
	JD_PST_MP_Mode_MP_Normal_Idle_Diff,
	JD_PST_MP_Mode_MP_LPWUG_Active,
	JD_PST_MP_Mode_MP_LPWUG_Active_Diff,
	JD_PST_MP_Mode_MP_LPWUG_Idle,
	JD_PST_MP_Mode_MP_LPWUG_Idle_Diff,
	JD_PST_MP_Mode_Short,
	JD_PST_MP_Mode_Open,
};

enum JD_MPAP_HANDSHAKE {
	JD_MPAP_HANDSHAKE_BUSY = 0x11,
    JD_MPAP_HANDSHAKE_FINISH = 0x22,
};

#endif
