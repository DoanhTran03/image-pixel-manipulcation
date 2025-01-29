#include <gtk/gtk.h>
#include <stdio.h>

// Callback function for button clicks
static void on_button1_clicked(GtkWidget *button, gpointer user_data) {
    g_print("Button 1 clicked\n");
}

static void on_button2_clicked(GtkWidget *button, gpointer user_data) {
    g_print("Button 2 clicked\n");
}

static void on_button3_clicked(GtkWidget *button, gpointer user_data) {
    g_print("Button 3 clicked\n");
}

// Function to render black background
static void draw_black_background(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    cairo_set_source_rgb(cr, 0, 0, 0);  // Set color to black
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);
}

// Callback function for application activation
static void on_app_activate(GtkApplication *app, gpointer user_data) {
    // Create the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello World GTK4 App");

    // Set the window size with a width to height ratio of 1.618
    int height = 300;
    int width = (int)(height * 1.618);
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    // Create a main horizontal box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    // Create the buttons bar with horizontal orientation
    GtkWidget *buttons_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(buttons_bar, "buttons_bar");

    GtkWidget *button1 = gtk_button_new_with_label("Button 1");
    GtkWidget *button2 = gtk_button_new_with_label("Button 2");
    GtkWidget *button3 = gtk_button_new_with_label("Button 3");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button2_clicked), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button3_clicked), NULL);

    gtk_box_append(GTK_BOX(buttons_bar), button1);
    gtk_box_append(GTK_BOX(buttons_bar), button2);
    gtk_box_append(GTK_BOX(buttons_bar), button3);

    // Create a vertical container for buttons and image area
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_append(GTK_BOX(content_box), buttons_bar);

    // Create the image area
    GtkWidget *image_area = gtk_drawing_area_new();
    gtk_widget_set_vexpand(image_area, TRUE);
    gtk_widget_set_hexpand(image_area, TRUE);

    // Set the drawing function for GTK4
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(image_area), draw_black_background, NULL, NULL);

    gtk_box_append(GTK_BOX(content_box), image_area);

    // Add the content box and image area to the main box
    gtk_box_append(GTK_BOX(main_box), content_box);

    gtk_window_set_child(GTK_WINDOW(window), main_box);

    // Apply CSS to set buttons_bar background color to grey
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider, "#buttons_bar { background-color: grey; border: 2px solid grey; }", -1);
    GtkStyleContext *style_context = gtk_widget_get_style_context(buttons_bar);
    gtk_style_context_add_provider(style_context, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    // Initialize GTK application
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.HelloWorld", G_APPLICATION_DEFAULT_FLAGS);

    // Activate signal for the application
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

    // Run the application
    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
