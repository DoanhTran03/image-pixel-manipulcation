#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>

static char *image_path = NULL;

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

// Function to render image or black background if no image provided
static void draw_image(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    if (!image_path) {
        cairo_set_source_rgb(cr, 0, 0, 0); // Set color to black if no image is provided
        cairo_rectangle(cr, 0, 0, width, height);
        cairo_fill(cr);
        return;
    }

    cairo_surface_t *image = cairo_image_surface_create_from_png(image_path);
    if (!g_file_test(image_path, G_FILE_TEST_EXISTS)) {
        g_printerr("Error: File not found - %s", image_path);
        return;
    }
    if (cairo_surface_status(image) != CAIRO_STATUS_SUCCESS) {
        g_print("Failed to load image: %s\n", image_path);
        cairo_surface_destroy(image);
        return;
    }

    int img_width = cairo_image_surface_get_width(image);
    int img_height = cairo_image_surface_get_height(image);
    double scale_x = (double)width / img_width;
    double scale_y = (double)height / img_height;
    double scale = scale_x < scale_y ? scale_x : scale_y;
    cairo_scale(cr, scale, scale);
    cairo_set_source_surface(cr, image, 0, 0);
    cairo_paint(cr);
    cairo_surface_destroy(image);
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
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(image_area), draw_image, NULL, NULL);

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

static int on_command_line(GApplication *app, GApplicationCommandLine *cmdline, gpointer user_data) {
    int argc;
    char **argv = g_application_command_line_get_arguments(cmdline, &argc);

    if (argc < 2) {
        g_printerr("Usage: %s <image_file.png>", argv[0]);
        return EXIT_FAILURE;
    }

    image_path = argv[1];
    g_application_activate(app);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        image_path = argv[1];
    }

    // Initialize GTK application
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.HelloWorld", G_APPLICATION_HANDLES_COMMAND_LINE);

    // Activate signal for the application
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
    g_signal_connect(app, "command-line", G_CALLBACK(on_command_line), NULL);

    // Run the application
    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
