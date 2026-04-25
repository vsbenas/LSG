enum TaskStatus
{
	TASK_PENDING = 0,
	TASK_IN_PROGRESS = 1,
	TASK_DONE = 2,
	TASK_CANCELLED = 3
};

enum TaskType
{
	SEND_SMS,
	SEND_EMAIL_REMINDER,
	SEND_EMAIL_VERIFICATION,
	SEND_EMAIL_NOTIFICATION
};

new const TaskNames[TaskType][] = {"SendSMS","SendEmailReminder","SendEmailVerification","SendEmailNotification"};

stock AddToTaskQueue(playerid, TaskType:type, message[])
{
	if(!IsPlayerConnected(playerid))
		return;
	new newmsg[2048];
	mysql_real_escape_string(message, newmsg);
	new query[5000];
	format(query,sizeof(query),"INSERT INTO `TaskQueue`(`task`,`name`,`message`,`status`,`created`) \
	VALUES ('%s','%s','%s',%i,NOW())",TaskNames[type], ReturnName(playerid), newmsg, _:TASK_PENDING);
	mysql_query(query);
}