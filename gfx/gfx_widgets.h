/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2018      - natinusala
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GFX_WIDGETS_H
#define _GFX_WIDGETS_H

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#include <formats/image.h>
#include <queues/task_queue.h>
#include <queues/message_queue.h>
#include <queues/fifo_queue.h>

#ifdef HAVE_THREADS
#include <rthreads/rthreads.h>
#endif

#include "gfx_animation.h"

#define DEFAULT_BACKDROP               0.75f

#define MSG_QUEUE_PENDING_MAX          32
#define MSG_QUEUE_ONSCREEN_MAX         4

#define MSG_QUEUE_ANIMATION_DURATION      330
#define TASK_FINISHED_DURATION            3000
#define HOURGLASS_INTERVAL                5000
#define HOURGLASS_DURATION                1000

/* TODO: Colors for warning, error and success */

#define TEXT_COLOR_INFO 0xD8EEFFFF
#if 0
#define TEXT_COLOR_SUCCESS 0x22B14CFF
#define TEXT_COLOR_ERROR 0xC23B22FF
#endif
#define TEXT_COLOR_FAINT 0x878787FF

enum gfx_widgets_icon
{
   MENU_WIDGETS_ICON_PAUSED = 0,
   MENU_WIDGETS_ICON_FAST_FORWARD,
   MENU_WIDGETS_ICON_REWIND,
   MENU_WIDGETS_ICON_SLOW_MOTION,

   MENU_WIDGETS_ICON_HOURGLASS,
   MENU_WIDGETS_ICON_CHECK,

   MENU_WIDGETS_ICON_INFO,

   MENU_WIDGETS_ICON_ACHIEVEMENT,

   MENU_WIDGETS_ICON_LAST
};

enum notification_show_screenshot_duration
{
   NOTIFICATION_SHOW_SCREENSHOT_DURATION_NORMAL = 0,
   NOTIFICATION_SHOW_SCREENSHOT_DURATION_FAST,
   NOTIFICATION_SHOW_SCREENSHOT_DURATION_VERY_FAST,
   NOTIFICATION_SHOW_SCREENSHOT_DURATION_INSTANT,
   NOTIFICATION_SHOW_SCREENSHOT_DURATION_LAST
};

enum notification_show_screenshot_flash
{
   NOTIFICATION_SHOW_SCREENSHOT_FLASH_NORMAL = 0,
   NOTIFICATION_SHOW_SCREENSHOT_FLASH_FAST,
   NOTIFICATION_SHOW_SCREENSHOT_FLASH_OFF,
   NOTIFICATION_SHOW_SCREENSHOT_FLASH_LAST
};

/* This structure holds all objects + metadata
 * corresponding to a particular font */
typedef struct
{
   font_data_t *font;
   video_font_raster_block_t raster_block; /* ptr alignment */
   size_t usage_count;
   unsigned glyph_width;
   float line_height;
   float line_ascender;
   float line_descender;
   float line_centre_offset;
} gfx_widget_font_data_t;

/* Font data */
typedef struct
{
   gfx_widget_font_data_t regular;
   gfx_widget_font_data_t bold;
   gfx_widget_font_data_t msg_queue;
} gfx_widget_fonts_t;

typedef struct cheevo_popup
{
   char* title;
   uintptr_t badge;
} cheevo_popup;

typedef struct disp_widget_msg
{
   char *msg;
   char *msg_new;
   retro_task_t *task_ptr;
   /* Used to detect title change */
   char *task_title_ptr;

   uint32_t task_ident;
   unsigned msg_len;
   unsigned duration;
   unsigned text_height;
   unsigned width;

   float msg_transition_animation;
   float offset_y;
   float alpha;
   float unfold;
   float hourglass_rotation;
   gfx_timer_t hourglass_timer; /* float alignment */
   gfx_timer_t expiration_timer; /* float alignment */

   int8_t task_progress;
   /* How many tasks have used this notification? */
   uint8_t task_count;

   bool task_finished;
   bool task_error;
   bool task_cancelled;
   bool expiration_timer_started;
   /* Is it currently doing the fade out animation ? */
   bool dying;
   /* Has the timer expired ? if so, should be set to dying */
   bool expired;
   /* Unfold animation */
   bool unfolded;
   bool unfolding;
} disp_widget_msg_t;

typedef struct dispgfx_widget
{
   uint64_t gfx_widgets_frame_count;

#ifdef HAVE_THREADS
   slock_t* current_msgs_lock;
#endif
   fifo_buffer_t *msg_queue;
   disp_widget_msg_t* current_msgs[MSG_QUEUE_ONSCREEN_MAX];
   gfx_widget_fonts_t gfx_widget_fonts; /* ptr alignment */

#ifdef HAVE_TRANSLATE
   uintptr_t ai_service_overlay_texture;
#endif
   uintptr_t msg_queue_icon;
   uintptr_t msg_queue_icon_outline;
   uintptr_t msg_queue_icon_rect;
   uintptr_t gfx_widgets_icons_textures[
   MENU_WIDGETS_ICON_LAST];
   uintptr_t gfx_widgets_generic_tag;

   size_t current_msgs_size;

#ifdef HAVE_TRANSLATE
   int ai_service_overlay_state;
#endif

   unsigned last_video_width;
   unsigned last_video_height;
   unsigned msg_queue_kill;
   /* Count of messages bound to a task in current_msgs */
   unsigned msg_queue_tasks_count;

   unsigned simple_widget_padding;
   unsigned simple_widget_height;

   /* Used for both generic and libretro messages */
   unsigned generic_message_height;

   unsigned msg_queue_height;
   unsigned msg_queue_spacing;
   unsigned msg_queue_rect_start_x;
   unsigned msg_queue_internal_icon_size;
   unsigned msg_queue_internal_icon_offset;
   unsigned msg_queue_icon_size_x;
   unsigned msg_queue_icon_size_y;
   unsigned msg_queue_icon_offset_y;
   unsigned msg_queue_scissor_start_x;
   unsigned msg_queue_default_rect_width_menu_alive;
   unsigned msg_queue_default_rect_width;
   unsigned msg_queue_regular_padding_x;
   unsigned msg_queue_regular_text_start;
   unsigned msg_queue_task_text_start_x;
   unsigned msg_queue_task_rect_start_x;
   unsigned msg_queue_task_hourglass_x;
   unsigned divider_width_1px;

   float last_scale_factor;
#ifdef HAVE_TRANSLATE
   unsigned ai_service_overlay_width;
   unsigned ai_service_overlay_height;
#endif

   char gfx_widgets_status_text[255];

   /* There can only be one message animation at a time to 
    * avoid confusing users */
   bool widgets_moving;
   bool widgets_inited;
   bool msg_queue_has_icons;
} dispgfx_widget_t;


/* A widget */
/* TODO: cleanup all unused parameters */
struct gfx_widget
{
   /* called when the widgets system is initialized
    * -> initialize the widget here */
   bool (*init)(bool video_is_threaded, bool fullscreen);

   /* called when the widgets system is freed
    * -> free the widget here */
   void (*free)(void);

   /* called when the graphics context is reset
    * -> (re)load the textures here */
   void (*context_reset)(bool is_threaded,
      unsigned width, unsigned height, bool fullscreen,
      const char *dir_assets, char *font_path,
      char* menu_png_path,
      char* widgets_png_path);

   /* called when the graphics context is destroyed
    * -> release the textures here */
   void (*context_destroy)(void);

   /* called when the window resolution changes
    * -> (re)layout the widget here */
   void (*layout)(void *data,
         bool is_threaded, const char *dir_assets, char *font_path);

   /* called every frame on the main thread
    * -> update the widget logic here */
   void (*iterate)(void *user_data,
      unsigned width, unsigned height, bool fullscreen,
      const char *dir_assets, char *font_path,
      bool is_threaded);

   /* called every frame
    * (on the video thread if threaded video is on)
    * -- data is a video_frame_info_t
    * -- userdata is a dispgfx_widget_t
    * -> draw the widget here */
   void (*frame)(void* data, void *userdata);
};

uintptr_t gfx_widgets_get_generic_tag(void *data);

unsigned gfx_widgets_get_padding(void *data);

unsigned gfx_widgets_get_divider_width(void *data);

unsigned gfx_widgets_get_height(void *data);

gfx_widget_font_data_t* gfx_widgets_get_font_regular(void *data);

gfx_widget_font_data_t* gfx_widgets_get_font_bold(void *data);

gfx_widget_font_data_t* gfx_widgets_get_font_msg_queue(void *data);

float* gfx_widgets_get_backdrop_orig(void);

unsigned gfx_widgets_get_last_video_width(void *data);

unsigned gfx_widgets_get_last_video_height(void *data);

unsigned gfx_widgets_get_generic_message_height(void *data);

/* Warning: not thread safe! */
size_t gfx_widgets_get_msg_queue_size(void *data);

float gfx_widgets_get_thumbnail_scale_factor(
      const float dst_width, const float dst_height,
      const float image_width, const float image_height);

void gfx_widgets_draw_icon(
      void *userdata,
      unsigned video_width,
      unsigned video_height,
      unsigned icon_width,
      unsigned icon_height,
      uintptr_t texture,
      float x, float y,
      float rotation, float scale_factor,
      float *color);

void gfx_widgets_draw_text(
      gfx_widget_font_data_t* font_data,
      const char *text,
      float x, float y,
      int width, int height,
      uint32_t color,
      enum text_alignment text_align,
      bool draw_outside);

void gfx_widgets_flush_text(
      unsigned video_width, unsigned video_height,
      gfx_widget_font_data_t* font_data);

typedef struct gfx_widget gfx_widget_t;

bool gfx_widgets_init(
      uintptr_t widgets_active_ptr,
      bool video_is_threaded,
      unsigned width, unsigned height, bool fullscreen,
      const char *dir_assets, char *font_path);

bool gfx_widgets_deinit(bool widgets_persisting);

void gfx_widgets_msg_queue_push(
      void *data,
      retro_task_t *task, const char *msg,
      unsigned duration,
      char *title,
      enum message_queue_icon icon,
      enum message_queue_category category,
      unsigned prio, bool flush,
      bool menu_is_alive);

void gfx_widget_volume_update_and_show(float new_volume,
      bool mute);

void gfx_widgets_iterate(
      void *data,
      unsigned width, unsigned height, bool fullscreen,
      const char *dir_assets, char *font_path,
      bool is_threaded);

void gfx_widget_screenshot_taken(void *data,
      const char *shotname, const char *filename);

/* AI Service functions */
#ifdef HAVE_TRANSLATE
bool gfx_widgets_ai_service_overlay_load(
      dispgfx_widget_t *p_dispwidget,
      char* buffer, unsigned buffer_len,
      enum image_type_enum image_type);

void gfx_widgets_ai_service_overlay_unload(dispgfx_widget_t *p_dispwidget);
#endif

#ifdef HAVE_CHEEVOS
void gfx_widgets_push_achievement(const char *title, const char *badge);
#endif

/* Warning: not thread safe! */
void gfx_widget_set_generic_message(
      void *data,
      const char *message, unsigned duration);

/* Warning: not thread safe! */
void gfx_widget_set_libretro_message(
      void *data,
      const char *message, unsigned duration);

/* Warning: not thread safe! */
void gfx_widget_set_progress_message(void *data,
      const char *message, unsigned duration,
      unsigned priority, int8_t progress);

/* Warning: not thread safe! */
bool gfx_widget_start_load_content_animation(void);

/* All the functions below should be called in
 * the video driver - once they are all added, set
 * enable_menu_widgets to true for that driver */
void gfx_widgets_frame(void *data);

void *dispwidget_get_ptr(void);

bool gfx_widgets_set_status_text(
      void *data,
      const char *new_status_text);

extern const gfx_widget_t gfx_widget_screenshot;
extern const gfx_widget_t gfx_widget_volume;
extern const gfx_widget_t gfx_widget_generic_message;
extern const gfx_widget_t gfx_widget_libretro_message;
extern const gfx_widget_t gfx_widget_progress_message;
extern const gfx_widget_t gfx_widget_load_content_animation;

#ifdef HAVE_CHEEVOS
extern const gfx_widget_t gfx_widget_achievement_popup;
#endif

#endif