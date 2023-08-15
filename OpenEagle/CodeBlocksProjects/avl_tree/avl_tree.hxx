/***************************************************************
 * Name:      avltree.hxx
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
#ifndef AVL_TREE
#define AVL_TREE
 struct avl_tree_node {
   struct avl_tree_node *next;
   struct avl_tree_node *last;
   struct avl_tree_node *taghist;
   unsigned char bi;
   char index[128];
   void * data_ptr;
};

struct avl_tree_node *initialize_avl_tree();
int erase_avl_tree(struct avl_tree_node * head);
struct avl_tree_node *convert_avl_tree_to_linked_list(struct avl_tree_node * head);
struct avl_tree_node *search_avl_tree (char * identifier, bool insert, struct avl_tree_node * root);
#endif
