#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>

static char *image_path = NULL;

// Function to render an image or black background if no image provided
static void draw_image(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    if (!image_path) {
        cairo_set_source_rgb(cr, 0, 0, 0); // Set background to black if no image is provided
        cairo_rectangle(cr, 0, 0, width, height);
        cairo_fill(cr);
        return;
    }

    // Load PNG image
    cairo_surface_t *image_surface = cairo_image_surface_create_from_png(image_path);
    printf("%s\n", cairo_status_to_string(cairo_surface_status(image_surface)));
    if (cairo_surface_status(image_surface) != CAIRO_STATUS_SUCCESS) {
        g_printerr("Error: Failed to load image - %s\n", image_path);
        cairo_surface_destroy(image_surface);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_rectangle(cr, 0, 0, width, height);
        cairo_fill(cr);
        return;
    }

    // Create a similar surface
    cairo_surface_t *composite_surface = cairo_surface_create_similar(image_surface, CAIRO_CONTENT_COLOR_ALPHA, width, height);
    cairo_t *composite_cr = cairo_create(composite_surface);

    cairo_set_source_surface(composite_cr, image_surface, 0, 0);
    cairo_paint(composite_cr);
    cairo_destroy(composite_cr);
    cairo_surface_destroy(image_surface);

    // Draw final composed image onto drawing area
    cairo_set_source_surface(cr, composite_surface, 0, 0);
    cairo_paint(cr);
    cairo_surface_destroy(composite_surface);
}

// Callback function for application activation
static void on_app_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "PNG Image Viewer");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *image_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(image_area, TRUE);
    gtk_widget_set_vexpand(image_area, TRUE);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(image_area), draw_image, NULL, NULL);

    gtk_window_set_child(GTK_WINDOW(window), image_area);
    gtk_window_present(GTK_WINDOW(window));
}

static int on_command_line(GApplication *app, GApplicationCommandLine *cmdline, gpointer user_data) {
    int argc;
    char **argv = g_application_command_line_get_arguments(cmdline, &argc);

    if (argc < 2) {
        g_printerr("Usage: %s <image_file.png>\n", argv[0]);
        return EXIT_FAILURE;
    }

    image_path = argv[1];
    g_application_activate(app);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.PngViewer", G_APPLICATION_HANDLES_COMMAND_LINE);

    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
    g_signal_connect(app, "command-line", G_CALLBACK(on_command_line), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
