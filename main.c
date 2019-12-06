#include <stdio.h>
#include <unistd.h>

#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/XPT7603.h"
#include "lvgl/lvgl.h"

#define DISP_BUF_SIZE (80*LV_HOR_RES_MAX)

// defining an event handler for example button presses
static void event_handler(lv_obj_t * obj, lv_event_t event)
{
  if(event == LV_EVENT_CLICKED) {
    printf("Clicked\n");
  }
  else if(event == LV_EVENT_VALUE_CHANGED) {
    printf("Toggled\n");
  }
}

// main program for lv_example
int main(int argc, char *argv[]) {
  
  printf("lv_init\n");
  /*LittlevGL init*/
  lv_init();
  
  /*Linux frame buffer device init*/
  fbdev_init();

  /*A small buffer for LittlevGL to draw the screen's content*/
  static lv_color_t buf[DISP_BUF_SIZE];

  /*Initialize a descriptor for the buffer*/
  static lv_disp_buf_t disp_buf;
  lv_disp_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

  /*Initialize and register a display driver*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.buffer = &disp_buf;
  disp_drv.flush_cb = fbdev_flush;
  lv_disp_drv_register(&disp_drv);
  
  /*Initialize and register an input device*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = xpt7603_read;      /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/
  
  /* Demo Code - replace this with yours */
  /*Create a "Hello world!" label*/
  lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label, "Hello world!");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  
  /*Create a button*/
  lv_obj_t * btnLabel;

  lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_event_cb(btn1, event_handler);
  lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 0);

  btnLabel = lv_label_create(btn1, NULL);
  lv_label_set_text(btnLabel, "Press Me");
  
  printf("starting loop\n");
  while(1) {
    lv_tick_inc(5);
    lv_task_handler();
    usleep(5000);
  }
  
  return 0;
}
