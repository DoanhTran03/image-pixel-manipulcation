#include <gtk/gtk.h>

int r, g, b, a;
static GtkWidget *color_box, *drawing_area;
static GdkTexture *texture = NULL;
cairo_surface_t *image_surface;
int button = 0;

static void getcolor (GtkWidget *widget, gpointer data)
{
  button = 1;
}
static void paint (GtkWidget *widget, gpointer data)
{
  button = 2;
}
static void redo (GtkWidget *widget, gpointer data)
{
  button = 3;
}
static void undo (GtkWidget *widget, gpointer data)
{
  button = 4;
}
static void save (GtkWidget *widget, gpointer data)
{
  button = 5;
}
void get_pixel_color_cairo(double x, double y) {
    if (!image_surface) return;
    unsigned char *data = cairo_image_surface_get_data(image_surface);
    int width = cairo_image_surface_get_width(image_surface);
    int height = cairo_image_surface_get_height(image_surface);
    int stride = cairo_image_surface_get_stride(image_surface);
    cairo_format_t format = cairo_image_surface_get_format(image_surface);

    if (x < 0 || x >= width || y < 0 || y >= height) {
        printf("Coordinates out of bounds\n");
        
        return;
    }

    int pixel_offset = y * stride + x * 4; // Assuming CAIRO_FORMAT_ARGB32
    b = data[pixel_offset + 0]; // Blue
    g = data[pixel_offset + 1]; // Green
    r = data[pixel_offset + 2]; // Red
    a = data[pixel_offset + 3]; // Alpha

    printf("Pixel at (%.2f, %.2f): R=%d, G=%d, B=%d, A=%d\n", x, y, r, g, b, a);
}
void change_pixel_color(double x, double y, int red, int green, int blue) {
    if (!image_surface) return;

    unsigned char *data = cairo_image_surface_get_data(image_surface);
    int width = cairo_image_surface_get_width(image_surface);
    int height = cairo_image_surface_get_height(image_surface);
    int stride = cairo_image_surface_get_stride(image_surface);

    if (x < 0 || x >= width || y < 0 || y >= height) {
        g_print("Pixel out of bounds\n");
        return;
    }

    int offset = y * stride + x * 4; // Each pixel has 4 bytes (RGBA)
    data[offset] = blue;   // Blue
    data[offset + 1] = green; // Green
    data[offset + 2] = red;   // Red
    data[offset + 3] = 255;   // Alpha (fully opaque)
    
    cairo_surface_flush(image_surface); // Ensure changes are written

    //image_surface = cairo_image_surface_create_for_data(data, CAIRO_FORMAT_ARGB32, width, height, stride);
}

static void on_mouse_click(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data) {
    g_print("Mouse clicked at (%.2f, %.2f) with %d presses\n", x, y, n_press);
    if(button == 1) {
        get_pixel_color_cairo(x, y);}
    if(button == 2);   {
        change_pixel_color(x, y, r, g, b);
    }

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
    if(drawing_area)    {
        gtk_widget_queue_draw(drawing_area);
        }
    if(color_box)   {
        gtk_widget_queue_draw(color_box);
        }
    return TRUE;
}

static void on_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    int w = cairo_image_surface_get_width(image_surface);
    int h = cairo_image_surface_get_height(image_surface);

    // Draw the image
    cairo_set_source_surface(cr, image_surface, 0, 0);
    cairo_paint(cr);
}

static void activate (GtkApplication* app, gpointer user_data)
{   
    const char *image_path = "test.png"; // Replace with your image file path
    // Load the image
    image_surface = cairo_image_surface_create_from_png(image_path);
    if (cairo_surface_status(image_surface) != CAIRO_STATUS_SUCCESS) {
        g_printerr("Failed to load image: %s\n", image_path);
        cairo_status_t status = cairo_surface_status(image_surface);
        g_printerr("Cairo error status: %d\n", status);
        return;
    }
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
    g_signal_connect (button, "clicked", G_CALLBACK (getcolor), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label ("Button 2");
    g_signal_connect (button, "clicked", G_CALLBACK (paint), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

    button = gtk_button_new_with_label ("Button 3");
    g_signal_connect (button, "clicked", G_CALLBACK (redo), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);

    button = gtk_button_new_with_label ("Button 4");
    g_signal_connect (button, "clicked", G_CALLBACK (undo), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);

    button = gtk_button_new_with_label ("Button 5");
    g_signal_connect (button, "clicked", G_CALLBACK (save), NULL);
    gtk_grid_attach (GTK_GRID (grid), button, 4, 0, 1, 1);

    color_box = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(color_box), on_color_box_draw, NULL, NULL);
    gtk_widget_set_size_request(color_box, 75, 10); // Set size for color box

    // Add widgets to layout
    gtk_grid_attach (GTK_GRID (grid), color_box, 5, 0, 1, 1);
    //gtk_box_append(GTK_BOX(vbox), color_box);

    drawing_area = gtk_drawing_area_new();
    gtk_box_append(GTK_BOX(vbox), drawing_area);
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), 700);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area), 700);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), on_draw, NULL, NULL);
    
    ////Loading mouse click event using gesture
    gtk_widget_set_hexpand(drawing_area, TRUE);
    gtk_widget_set_vexpand(drawing_area, TRUE);

    //g_timeout_add(16, on_timer, vbox);
    g_timeout_add(16, on_timer, NULL);

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