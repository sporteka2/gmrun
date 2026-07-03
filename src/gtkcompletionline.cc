#include "gtkcompletionline.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <glib.h>

G_DEFINE_TYPE(GtkCompletionLine, gtk_completion_line, GTK_TYPE_ENTRY)

static void gtk_completion_line_init(GtkCompletionLine *cl) {
  cl->tabtimeout = 0;
}

static void gtk_completion_line_class_init(GtkCompletionLineClass *klass) {
  /* GTK3: signals are emitted manually from key handler */
}

GtkWidget* gtk_completion_line_new(void) {
  return GTK_WIDGET(g_object_new(GTK_TYPE_COMPLETION_LINE, NULL));
}

gint gtk_completion_line_last_history_item(GtkCompletionLine *cl) {
  if (!GTK_IS_COMPLETION_LINE(cl)) return 0;
  return 0;
}
string quote_string(const string& str)
{
  string res;
  const char* i = str.c_str();
  while (*i) {
    char c = *i++;
    switch (c) {
     case ' ':
      res += '\\';
     default:
      res += c;
    }
  }
  return res;
}

static void
get_token(istream& is, string& s)
{
  s.clear();
  bool escaped = false;
  while (!is.eof()) {
    char c = is.get();
    if (is.eof())
      break;
    if (escaped) {
      s += c;
      escaped = false;
    } else if (c == '\\') {
      // s += c;
      escaped = true;
    } else if (::isspace(c)) {
      while (::isspace(c) && !is.eof()) c = is.get();
      if (!is.eof())
        is.unget();
      break;
    } else {
      s += c;
    }
  }
}

int
get_words(GtkCompletionLine *object, vector<string>& words)
{
  string content(gtk_entry_get_text(GTK_ENTRY(object)));
  int pos_in_text = gtk_editable_get_position(GTK_EDITABLE(object));
  int pos = 0;
  {
    string::iterator i = content.begin() + pos_in_text;
    if (i != content.end())
      content.insert(i, ' ');
  }
  istringstream ss(content);

  while (!ss.eof()) {
    string s;
    // ss >> s;
    get_token(ss, s);
    words.push_back(s);
    if (ss.eof()) break;
    if (ss.tellg() < pos_in_text && ss.tellg() >= 0)
      ++pos;
  }

  return pos;
}
