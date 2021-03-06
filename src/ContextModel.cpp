/*
 * ContexModel.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: khajvah
 */

#include "ContextModel.h"


ContextModel::ContextModel() {
	m_mainModel = ListModel::Instance();
	this->setSortedAscending(false);

	QStringList keyList;
	//keyList << "Status" << "DateCreated";
	m_folderName = 0;
	//this->setSortingKeys(keyList);

	connect (m_mainModel, SIGNAL(newTaskAdded(QVariantMap)), this, SLOT(onNewTaskAdded(QVariantMap)));
	connect (m_mainModel, SIGNAL(taskRemoved(int)), this, SLOT(onTaskRemoved(int)));
	connect (m_mainModel, SIGNAL(statusChanged(int, QString)), this, SLOT(onStatusChanged(int,QString)));
	connect (m_mainModel, SIGNAL(entryReplaced(int,QVariantMap)), this, SLOT(onEntryReplaced(int, QVariantMap)));
}

void ContextModel::fillmdata (QVariantList it) {
	m_data.append(this->data(it));
}

ContextModel::~ContextModel() {
	// TODO Auto-generated destructor stub
}

void ContextModel::searchData (QString searchWord) {
	this->clear();
	if (m_folderName != 0)
		for (unsigned int i = 0; i < m_mainModel->getData().size(); i++) {
			if (m_mainModel->getData().at(i).toMap()["Description"].toString().startsWith(searchWord, Qt::CaseInsensitive) &&
					m_mainModel->getData().at(i).toMap()["Folder"].toInt() == m_folderName) {
				this->insert(m_mainModel->getData().at(i).toMap());
			}
		}
	else
		for (unsigned int i = 0; i < m_mainModel->getData().size(); i++) {
			if (m_mainModel->getData().at(i).toMap()["Description"].toString().startsWith(searchWord, Qt::CaseInsensitive)) {
				this->insert(m_mainModel->getData().at(i).toMap());
			}
		}
}


int ContextModel::folder() {
	return m_folderName;
}

void ContextModel::setFolder(int FolderName) {
	m_folderName = FolderName;
}

void ContextModel::fillEntire () {

	this->insertList(m_mainModel->getData());

	//	QVariantList it = m_mainModel->first();
	//	for (unsigned int i = 0; i < m_mainModel->size(); i++) {
	//		this->insert(m_mainModel->data(it).toMap());
	//		it = m_mainModel->after(it);
	//	}
	QStringList keyList;
	keyList << "Status" << "DateCreated";
	this->setSortingKeys(keyList);

	//A bug in BB SDK. Have to put following after insert(...)
	this->setSortedAscending(false);

}

void ContextModel::fillByFolderId (int folderid) {
	this->clear();
	for (unsigned int i = 0; i < m_mainModel->getData().size(); i++) {
		if (m_mainModel->getData().at(i).toMap()["Folder"].toInt() == m_folderName) {
			this->insert(m_mainModel->getData().at(i).toMap());
		}
	}
	QStringList keyList;
	keyList << "Status" << "DateCreated";
	this->setSortingKeys(keyList);

	//A bug in BB SDK. Have to put following after insert(...)
	this->setSortedAscending(false);
}


int ContextModel::addNewTask ( int folderName, QString description, QDateTime dateToFinish, int isReminded,
		int quantity, int price) {

	return m_mainModel->addNewTask(folderName, description, dateToFinish, isReminded, quantity, price, NULL);

}

int ContextModel::removeTask (int dateCreated) {
	return m_mainModel->removeTask(dateCreated);
}

bool ContextModel::isReminded (int taskID) {
	return m_mainModel->isReminded(taskID);
}

int ContextModel::replaceEntry (int taskID, QString newDescription, QDateTime newDateToFinish, int newisReminded) {
	return m_mainModel->replaceEntry(taskID, newDescription, newDateToFinish, newisReminded);
}

int ContextModel::changeStat (int dateCreated, QString taskStatus) {
	return m_mainModel->changeStat(dateCreated, taskStatus);
}

QString ContextModel::getDesctiption(int id) {
	return m_mainModel->getDesctiption(id);
}

QString ContextModel::getDatetoFinish(int id) {
	return m_mainModel->getDatetoFinish(id);
}

int ContextModel::getStatus (int id) {
	return m_mainModel->getStatus(id);
}

void ContextModel::onNewTaskAdded (QVariantMap newtask) {
	if (m_folderName == newtask["Folder"].toInt())
		this->insert(newtask);
}

void ContextModel::onTaskRemoved (int id) {
	QVariantList it = this->first();
	for (unsigned int i = 0; i < this->size(); i++) {
		if (this->data(it).toMap()["DateCreated"].toInt() == id) {
			this->removeAt(it);
			return;
		}
		it = this->after(it);
	}
}

void ContextModel::onStatusChanged (int id, QString newStatus) {
	QVariantMap updatedData;
	QVariantList it = this->first();
	for (unsigned int i = 0; i < this->size(); i++) {
		if (this->data(it).toMap()["DateCreated"] == id) {
			updatedData = this->data(it).toMap();
			updatedData["Status"] = newStatus;
			this->updateItem(it, updatedData);
			break;
		}
		it = this->after(it);
	}
}

void ContextModel::onEntryReplaced (int id, QVariantMap newEntry) {
	QVariantList it = this->first();
	for (unsigned int i = 0; i < this->size(); i++) {
		if (this->data(it).toMap()["DateCreated"].toInt() == id) {
			this->updateItem(it, newEntry);
			break;
		}
		it = this->after(it);
	}
}


