#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *align;
  GtkWidget *view;
  GtkTextBuffer *buffer;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "example_gtk");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
  gtk_container_set_border_width(GTK_CONTAINER(window), 15);
  
  view = gtk_text_view_new ();
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (view));
  gtk_text_buffer_set_text (buffer, "テキスト", -1);

  align = gtk_alignment_new(0, 0, 0, 0);
  gtk_container_add(GTK_CONTAINER(align), view);
  gtk_container_add(GTK_CONTAINER(window), align);  

  gtk_widget_show_all(window);
  
  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;
}

