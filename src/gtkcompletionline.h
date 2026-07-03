#ifndef __GTK_COMPLETION_LINE_H__
#define __GTK_COMPLETION_LINE_H__

#include <gtk/gtk.h>
#include "history.h"

G_BEGIN_DECLS

#define GTK_TYPE_COMPLETION_LINE            (gtk_completion_line_get_type())
#define GTK_COMPLETION_LINE(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_COMPLETION_LINE, GtkCompletionLine))
#define GTK_COMPLETION_LINE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass), GTK_TYPE_COMPLETION_LINE, GtkCompletionLineClass))
#define GTK_IS_COMPLETION_LINE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_COMPLETION_LINE))
#define GTK_IS_COMPLETION_LINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), GTK_TYPE_COMPLETION_LINE))
#define GTK_COMPLETION_LINE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_COMPLETION_LINE, GtkCompletionLineClass))

typedef struct _GtkCompletionLine      GtkCompletionLine;
typedef struct _GtkCompletionLineClass GtkCompletionLineClass;

typedef void (*GtkCompletionLineFunc) (GtkCompletionLine *cl, gpointer data);

enum GCL_SEARCH_MODE
{
  GCL_SEARCH_OFF = 0,
  GCL_SEARCH_REW = 1,
  GCL_SEARCH_FWD = 2,
  GCL_SEARCH_BEG = 3
};

struct _GtkCompletionLine {
  GtkEntry parent_instance;
  gint tabtimeout;
  gboolean show_dot_files;
  GList *where;
  HistoryFile *hist;
  GCL_SEARCH_MODE hist_search_mode;
  std::string *hist_word;
  int first_key;
};

struct _GtkCompletionLineClass {
  GtkEntryClass parent_class;
};

GType      gtk_completion_line_get_type (void) G_GNUC_CONST;
GtkWidget* gtk_completion_line_new      (void);

gint gtk_completion_line_last_history_item (GtkCompletionLine *cl);

G_END_DECLS

#endif
