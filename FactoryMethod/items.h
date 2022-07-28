#pragma once

enum ItemTier {
	Thrash,
	Mediocre,
	Standard,
	Refined,
	Excellent,
	Rare, 
	Legendary,
	Unique,
	God,
	Demon
};


class Item {
	//there should be a list in DB with all the item stats level name etc 
public:
	//Enchant m_enchant;
	ItemTier m_itemTier;
	int m_durability;
	int m_damage;
	int m_itemLevel;

	//no except and things like that ?
	Item(int durability, int damage, int itemLevel) : m_durability{ durability }, m_damage{ damage }, m_itemLevel{ itemLevel } {}

};