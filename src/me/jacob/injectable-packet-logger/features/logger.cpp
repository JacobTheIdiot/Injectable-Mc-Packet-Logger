#include "logger.h"
void log_packets(JNIEnv* env, JavaVM* jvm)
{
	//get mc
	jclass minecraftClass = env->FindClass("ave");
	jmethodID getMinecraftMethod = env->GetStaticMethodID(minecraftClass, "A", "()Lave;");
	jobject mc = env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);

	//get the player
	jfieldID thePlayerField = env->GetFieldID(minecraftClass, "h", "Lbew;");
	jobject player = env->GetObjectField(mc, thePlayerField);
	if (player == NULL)
	{
		std::cerr << "failed to get player! are you in game?" << std::endl;
		return;
	}

	// get the sendQueue
	jclass playerClass = env->GetObjectClass(player);
	jfieldID sendQueueField = env->GetFieldID(playerClass, "a", "Lbjb;");
	jobject sendQueue = env->GetObjectField(player, sendQueueField);

	// get NetworkManager
	jclass sendQueueClass = env->GetObjectClass(sendQueue);
	jfieldID networkManagerField = env->GetFieldID(sendQueueClass, "i", "Lek;");
	jobject networkManager = env->GetObjectField(sendQueue, networkManagerField);

	//gonna add a while loop here probably then print and get packets in there
}
