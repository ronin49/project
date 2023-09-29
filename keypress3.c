/*
 * 
 * compile command:
 * 
 * gcc keypress3.c -o keypress3  `pkg-config --libs --cflags gtk+-2.0`
 * 
 */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data);

int main (int argc, char *argv[])
{
  GtkWidget *window;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_key_press), NULL);


GtkWidget *view;
GtkTextBuffer *buffer;

view = gtk_text_view_new ();

buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

gtk_text_buffer_set_text (buffer, "Hello, this is some text", -1);

/* Now you might put the view in a container and display it on the
 * screen; when the user edits the text, signals on the buffer
 * will be emitted, such as "changed", "insert_text", and so on.
 */


gtk_container_add(GTK_CONTAINER(window), view);  

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}

gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  switch (event->keyval)
  {
    case GDK_p:
      printf("key pressed: %s\n", "p");
      break;
    case GDK_S:
    case GDK_s:
      if (event->state & GDK_SHIFT_MASK)
      {
        printf("key pressed: %s\n", "shift + s");
      }
      else if (event->state & GDK_CONTROL_MASK)
      {
        printf("key pressed: %s\n", "ctrl + s");
      }
      else
      {
        printf("key pressed: %s\n", "s");
      }
      break;
    case GDK_m:
      if (event->state & GDK_SHIFT_MASK)
      {
        printf("key pressed: %s\n", "shift + m");
      }
      else if (event->state & GDK_CONTROL_MASK)
      {
        printf("key pressed: %s\n", "ctrl + m");
      }
      else
      {
        printf("key pressed: %s\n", "m");
      }
      break;

    default:
      return FALSE; 
  }

  return FALSE; 
}
