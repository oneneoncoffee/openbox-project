#include <stdlib.h>
#include <gtk/gtk.h>

static void Aboutprog (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;
  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "This program was written in GTK+ / GCC C compiler and is open source and free to use build on. Progammed by Johnny B Stroud. ");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

static void runhtop (GtkWidget *wid, GtkWidget *win) {
system("htop");
}

static void rungedit (GtkWidget *wid, GtkWidget *win) {
system("gedit");
}

static void runbashtop (GtkWidget *wid, GtkWidget *win) {
system("bashtop");
}

int main (int argc, char *argv[])
{
  GtkWidget *button = NULL;
  GtkWidget *win = NULL;
  GtkWidget *label = NULL;
  GtkWidget *vbox = NULL;

  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_title (GTK_WINDOW (win), "Wiblex");
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_MOUSE);  // follow the mouse
  gtk_window_set_default_size(GTK_WINDOW(win), 200, 150);
  gtk_widget_realize (win);

  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  vbox = gtk_vbox_new (TRUE, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  label = gtk_label_new(NULL);
  const char *str = "MAIN MENU OPTIONS";
  const char *format = "<u>%s</u>";
  char *markup;
   markup = g_markup_printf_escaped (format, str);
   gtk_label_set_markup (GTK_LABEL (label), markup);
   g_free (markup);
   gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
   gtk_widget_set_tooltip_text (button, "Information about program.");
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (Aboutprog), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  button = gtk_button_new();
  char *ButtonStance = "Launch geditor";
  GtkWidget *EntryButton = gtk_button_new_with_label(ButtonStance);
  g_signal_connect (G_OBJECT (EntryButton), "clicked", G_CALLBACK (rungedit), (gpointer) win);
  gtk_widget_set_tooltip_text (EntryButton, "Click this to run gedit program.");
  gtk_box_pack_start(GTK_BOX(vbox), EntryButton, TRUE, TRUE, 0);

  button = gtk_button_new();
  char *ButtonStance2 = "Launch htop";
  GtkWidget *EntryButton2 = gtk_button_new_with_label(ButtonStance2);
  gtk_widget_set_tooltip_text (EntryButton2, "This will run HTOP a console stats app. Note: If it errors out please install htop (sudo apt install htop).");
  g_signal_connect (G_OBJECT (EntryButton2), "clicked", G_CALLBACK (runhtop), (gpointer) win);
  gtk_box_pack_start(GTK_BOX(vbox), EntryButton2, TRUE, TRUE, 0);

  button = gtk_button_new();
  char *ButtonStance3 = "Launch bashtop";
  GtkWidget *EntryButton3 = gtk_button_new_with_label(ButtonStance3);
  gtk_widget_set_tooltip_text (EntryButton3, "This will run bashtop a console stats app. Note: if you don't hace bash 4.4.0 this will not work. So and/or if bashtop is not installed try sudo apt install bashtop to correct.");
  g_signal_connect (G_OBJECT (EntryButton3), "clicked", G_CALLBACK (runbashtop), (gpointer) win);
  gtk_box_pack_start(GTK_BOX(vbox), EntryButton3, TRUE, TRUE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", gtk_main_quit, NULL);
  gtk_widget_set_tooltip_text (button, "Click to exit program.");
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  /* Enter the main loop */
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
