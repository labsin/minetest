/*
Minetest
Copyright (C) 2010-2013 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef NODEMETADATA_HEADER
#define NODEMETADATA_HEADER

#include "metadata.h"

/*
	NodeMetadata stores arbitary amounts of data for special blocks.
	Used for furnaces, chests and signs.

	There are two interaction methods: inventory menu and text input.
	Only one can be used for a single metadata, thus only inventory OR
	text input should exist in a metadata.
*/

class Inventory;
class IItemDefManager;

class NodeMetadata : public Metadata
{
public:
	NodeMetadata(IItemDefManager *item_def_mgr);
	~NodeMetadata();

	void serialize(std::ostream &os) const;
	void deSerialize(std::istream &is);

	void clear();
	bool empty() const;

	// The inventory
	Inventory *getInventory()
	{
		return m_inventory;
	}

private:
	Inventory *m_inventory;
};


/*
	List of metadata of all the nodes of a block
*/

class NodeMetadataList
{
public:
	~NodeMetadataList();

	void serialize(std::ostream &os) const;
	void deSerialize(std::istream &is, IItemDefManager *item_def_mgr);

	// Add all keys in this list to the vector keys
	std::vector<v3s16> getAllKeys();
	// Get pointer to data
	NodeMetadata *get(v3s16 p);
	// Deletes data
	void remove(v3s16 p);
	// Deletes old data and sets a new one
	void set(v3s16 p, NodeMetadata *d);
	// Deletes all
	void clear();

private:
	int countNonEmpty() const;

	std::map<v3s16, NodeMetadata *> m_data;
};

#endif
