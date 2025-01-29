#include <gtk/gtk.h>

int r, g, b, a;
static GtkWidget *color_box;
static GdkTexture *texture = NULL;

static void print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World\n");
}

static void get_pixel_color(double x, double y) {
    if (!texture) return;

    int width = gdk_texture_get_width(texture);
    int height = gdk_texture_get_height(texture);

    // Ensure clicked coordinates are within bounds
    if (x < 0 || y < 0 || x >= width || y >= height) return;

    // Create buffer to store pixel data
    int stride = width * 4; // 4 bytes per pixel (RGBA)
    guchar *pixel_data = g_malloc(stride * height);
    if (!pixel_data) return;

    // Download texture pixels into buffer
    gdk_texture_download(texture, pixel_data, stride);

    // Get pixel color at (x, y)
    int row = ((int)y) * stride;
    int col = ((int)x) * 4; // 4 bytes per pixel

    b = pixel_data[row + col + 0]; // Red
    g = pixel_data[row + col + 1]; // Green
    r = pixel_data[row + col + 2]; // Blue
    a = pixel_data[row + col + 3]; // Alpha

    g_print("Color at (%.2f, %.2f): R=%d, G=%d, B=%d, A=%d\n", x, y, r, g, b, a);
    // Free allocated memory
    g_free(pixel_data);
}

static void on_mouse_click(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data) {
    g_print("Mouse clicked at (%.2f, %.2f) with %d presses\n", x, y, n_press);
    get_pixel_color(x, y);

}
void set_color(cairo_t *cr) {
    double red = (double)r/255.0;
    double green = (double)g/255.0;
    double blue = (double)b/255.0;
    double alpha = (double)a/255.0;
    cairo_set_source_rgba(cr, red, green, blue, alpha);
}
static void on_color_box_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    set_color(cr);
    cairo_rectangle(cr, 0, 0, 100, 100);
    cairo_fill_preserve(cr);

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_set_font_size(cr, 15.0);
    char iteration_label[50];
    cairo_move_to(cr, 20, 20);
    sprintf(iteration_label, "Color");
    cairo_show_text(cr, iteration_label);
}
gboolean on_timer(gpointer user_data) {
    GtkWidget *drawing_area = GTK_WIDGET(user_data);
    gtk_widget_queue_draw(drawing_area);
    return TRUE;
}

static gboolean on_mouse_press(GtkWidget *widget, GdkEvent *event, gpointer data) {
    double x, y;

    // Get the position of the event (mouse click)
    gdk_event_get_position(event, &x, &y);

    // Print the position
    g_print("Mouse clicked at position: (%d, %d)\n", x, y);

    return FALSE; // Returning FALSE allows the event to propagate further
}


static void on_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    const char *image_path = "test.png"; // Replace with your image file path
    cairo_surface_t *image_surface;

    // Load the image
    image_surface = cairo_image_surface_create_from_png(image_path);
    texture = gdk_texture_new_from_filename(image_path, NULL);

    //texture = gdk_texture_new_for_surface(image_surface);


    // Check for errors
    if (cairo_surface_status(image_surface) != CAIRO_STATUS_SUCCESS) {
        g_printerr("Failed to load image: %s\n", image_path);
        cairo_status_t status = cairo_surface_status(image_surface);
        g_printerr("Cairo error status: %d\n", status);
        return;
    }

    //Scaling the image, will not work when load the picture to have the color
    // Get image dimensions
    // int img_width = cairo_image_surface_get_width(image_surface);
    // int img_height = cairo_image_surface_get_height(image_surface);

    // // Scale the image to fit the drawing area
    // double scale_x = (double)width / img_width;
    // double scale_y = (double)height / img_height;
    // double scale = (scale_x < scale_y) ? scale_x : scale_y;

    // // Center the image in the drawing area
    // double offset_x = (width - img_width * scale) / 2.0;
    // double offset_y = (height - img_height * scale) / 2.0;

    // // Apply transformations
    // cairo_translate(cr, offset_x, offset_y);
    // cairo_scale(cr, scale, scale);

    // Draw the image
    cairo_set_source_surface(cr, image_surface, 0, 0);
    cairo_paint(cr);

    // Clean up
    cairo_surface_destroy(image_surface);
}

static void activate (GtkApplication* app, gpointer user_data)
{   

    //Loading window, button, and picture
    GtkWidget *button;

    GtkWidget *window;
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 800);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    GtkWidget *grid = gtk_grid_new ();

    /* Pack the container in the window */
    gtk_box_append(GTK_BOX(vbox), grid);

    button = gtk_button_new_with_label ("Button 1");
    g_signal_connect (button, "clicked", G_CALLBACK (on_mouse_press), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label ("Button 2");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

    button = gtk_button_new_with_label ("Button 3");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);

    button = gtk_button_new_with_label ("Button 4");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);

    button = gtk_button_new_with_label ("Button 5");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 4, 0, 1, 1);

    color_box = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(color_box), on_color_box_draw, NULL, NULL);
    gtk_widget_set_size_request(color_box, 75, 10); // Set size for color box

    // Add widgets to layout
    gtk_grid_attach (GTK_GRID (grid), color_box, 5, 0, 1, 1);
    //gtk_box_append(GTK_BOX(vbox), color_box);
    g_timeout_add(16, on_timer, color_box);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_box_append(GTK_BOX(vbox), drawing_area);
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), 700);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area), 700);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), on_draw, NULL, NULL);

    ////Loading mouse click event using gesture
    gtk_widget_set_hexpand(drawing_area, TRUE);
    gtk_widget_set_vexpand(drawing_area, TRUE);

    // Create a mouse click gesture detector
    GtkGesture *click_gesture = gtk_gesture_click_new();
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(click_gesture), 0); // 0 = Any mouse button

    // Connect the gesture's signal to our callback function
    g_signal_connect(click_gesture, "pressed", G_CALLBACK(on_mouse_click), NULL);

    // Add the controller
    gtk_widget_add_controller(drawing_area, GTK_EVENT_CONTROLLER(click_gesture));

    gtk_window_present (GTK_WINDOW (window));
    
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}