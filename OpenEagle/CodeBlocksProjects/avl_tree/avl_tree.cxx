/***************************************************************
 * Name:      avltree.cxx
 * Purpose:   avl tree unit for managing lists for look ups to cross reference data such as airport to tower, airport to ils data etc.
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2005
 * Copyright: Philip Cobbin (cobbin.com)
 * License    GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.html
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later versio
 *
 * This library is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Lice
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 **************************************************************/
//----------------------------------------- avl tree list processing...linked list searching performance declines sharply as  N grows
#include <string.h>
#include "avl_tree.hxx"
#include <stdio.h>
#include <stdlib.h>
#define LEFTH 1
#define RIGHTH 2
#define BALANCED 3

struct avl_tree_node *tree_path[100001];  // need error check on blowing it
unsigned int tree_direction[100001];

struct avl_tree_node *initialize_avl_tree()
{
  struct avl_tree_node * new_root;
  new_root =  new struct avl_tree_node;
  new_root->taghist = NULL;
  new_root->bi = LEFTH;
  new_root->last = new_root;
  strcpy (new_root->index,"n a s");
  return new_root;
}

struct avl_tree_node *add_node_to_tree (char * identifier)
{
  struct avl_tree_node * new_node;
  new_node =  new struct avl_tree_node;
  new_node->data_ptr=NULL;
  new_node->bi = BALANCED;
  new_node->next = NULL;
  new_node->last = NULL;
  strcpy (new_node->index,identifier);
  return new_node;
}

struct avl_tree_node *search_avl_tree (char * identifier, bool insert, struct avl_tree_node * root)
{
  int inserted;
  struct avl_tree_node *t,
                       *f,
                       *x,
                       *y,
                       *z;
  int i,
      d,
  level,
  mark;
  int done;
  struct avl_tree_node * function = NULL;

  inserted = false;

  struct avl_tree_node *new_node = NULL;
  if (root==NULL) {
    printf("\n\n\n null root node! \n\n\n");
    exit(1);
  }
  if (root->last == root) {
    if (insert) {
      new_node = add_node_to_tree(identifier);
      root->last = new_node;
      root->taghist = new_node;
      new_node->taghist = NULL;
      t = new_node;
      function = new_node;
      return(function);
    }
    else  {
      function = NULL;
      return(function);
    }
  }
  else  {
    level = 0;
    tree_path[level] = root;
    t = root->last;
    done = false;
    while ( ! done) {
      if (strcmp(identifier,t->index) < 0 ) {
 	if (t->last != NULL) {
	  level = level + 1;
	  tree_path[level] = t;
	  tree_direction[level] = LEFTH;
	  t = t->last;
	}
	else  {
          if (insert) {
 	    inserted = true;
            new_node = add_node_to_tree(identifier);
            new_node->taghist = root->taghist;
            root->taghist = new_node;
            t->last = new_node;
            level = level + 1;
            tree_path[level] = t;
            tree_direction[level] = LEFTH;
            done = true;
            function = new_node;
          }
          else  {
            done = true;
            function = NULL;
          }
        }
      }
      else  {
        if (strcmp(identifier,t->index) >0 ) {
          if (t->next != NULL) {
            level = level + 1;
            tree_path[level] = t;
            tree_direction[level] = RIGHTH;
            t = t->next;
          }
          else  {
            if (insert) {
              inserted = true;
              level = level + 1;
              new_node = add_node_to_tree(identifier);
              new_node->taghist = root->taghist;
              root->taghist = new_node;
              tree_path[level] = t;
              tree_direction[level] = RIGHTH;
              t->next = new_node;
              done = true;
              function = new_node;
	    }
            else  {
              done = true;
              function = NULL;
	    }
          }
        }
        else  {
          done = true;
          function = t;
          return(function);
        }
      }
    }
  }
  if ( ! inserted) return(function);
  /* search for an unbalanced node*/
  mark = level;
  i = level;
  struct avl_tree_node * a_node;
  a_node = tree_path[i];
  while (a_node->bi == BALANCED) {
    i = i - 1;
    mark = i;
    a_node = tree_path[i];
  }
  /*adjust balance indicators*/
  for (i = mark + 1; i <= level; i++) {
    if (strcmp(identifier,tree_path[i]->index) < 0) tree_path[i]->bi = LEFTH; else tree_path[i]->bi = RIGHTH;
  }
  /*is there a critical node?*/
  if (mark == 0) return(function);
  d = tree_direction[mark];
  x = tree_path[mark];
  y = tree_path[mark + 1];
  if (x->bi != d) {
    x->bi = BALANCED;
    /*was heavy but now balanced*/
    return(function);
  }
  /*rebalancing: single rotation*/
  if (y->bi == d) {
    if (d == LEFTH) {
      x->last = y->next;
      y->next = x;
    }
    else  {
      x->next = y->last;
      y->last = x;
    }
    x->bi = BALANCED;
    y->bi = BALANCED;
    f = tree_path[mark - 1];
    if (x == f->last)  f->last = y; else  f->next = y;
    return(function);
  }
  /*rebalancing: double rotation; a) change structural links*/
  if (d == LEFTH) {
    z = y->next;
    y->next = z->last;
    z->last = y;
    x->last = z->next;
    z->next = x;
  }
  else  {
    z = y->last;
    y->last = z->next;
    z->next = y;
    x->next = z->last;
    z->last = x;
  }
  f = tree_path[mark - 1];
  if (x == f->last) f->last = z; else f->next = z;
  /*b change balance indicators*/
  if (z->bi == d) {
    y->bi = BALANCED;
    z->bi = BALANCED;
    if (d == LEFTH) x->bi = RIGHTH; else  x->bi = LEFTH;
  }
  else  {
    if (z->bi == BALANCED) {
      z->bi = BALANCED;
      y->bi = BALANCED;
      x->bi = BALANCED;
    }
    else  {
      z->bi = BALANCED;
      x->bi = BALANCED;
      y->bi = d;
    }
  }
  return(function);
}

int erase_avl_tree(struct avl_tree_node * head)
{
  int erase_count=0;
  struct avl_tree_node *t;
  struct avl_tree_node *tt;
  t = head->taghist;
  while (t != NULL) {
    tt=t;
    t = t->taghist;
    delete tt; erase_count++;
  }
  head = NULL;
  return erase_count;
}

struct avl_tree_node * convert_avl_tree_to_linked_list(struct avl_tree_node * head)
{
  struct avl_tree_node *list_ptr;
  struct avl_tree_node *t,
                       *x,
                       *y,
                       *z;
  int inserted;
  t = head->taghist;
  list_ptr = NULL;
  while (t != NULL) {
    z = t;
    t = t->taghist;
    if (list_ptr == NULL) {
      list_ptr = z;
      z->taghist = NULL;
    }
    else  {
      inserted = false;
      y = list_ptr;
      x = NULL;
      while ( ! inserted) {
	if (strcmp(z->index,y->index) >= 0) {
	  if (y->taghist == NULL) {
	    y->taghist = z;
	    z->taghist = NULL;
	    inserted = true;
	  }
	  else  {
	    x = y;
	    y = y->taghist;
	  }
	}
	else  {
	  if (x == NULL) {
	    z->taghist = list_ptr;
	    list_ptr = z;
	    inserted = true;
	  }
	  else  {
	    x->taghist = z;
	    z->taghist = y;
	    inserted = true;
	  }
        }
      }
    }
  }
  t = list_ptr;
  if (t != NULL) {
    t->last = NULL;
    t->next = t->taghist;
    if (t->next != NULL) t->next->last = t;
    t = t->taghist;
    while (t != NULL) {
      t->next = t->taghist;
      if (t->next != NULL) t->next->last = t;
      t = t->taghist;
    }
  }
  delete head;
  head=list_ptr;
  return head;
}
