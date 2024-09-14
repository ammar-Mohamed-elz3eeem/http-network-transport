/**
 * @file: HTTPNetworkTransport.cpp
 * @author: Ammar Massoud (ammar@wpkama.com)
 * 
 * @brief
 *     This file tests class HTTPNetworkTransport::HTTPNetworkTransport
 * 
 * @version: 1.0.0
 * @date: 2024-07-28
 * @copyright: Copyright (c) 2024
 */

#include <gtest/gtest.h>
#include <HTTPNetworkTransport/HTTPServerNetworkTransport.hpp>
#include <SystemAbstractions/NetworkConnection.hpp>
#include <HTTP/Connection.hpp>
#include <condition_variable>
#include <gtest/gtest.h>
#include <vector>
#include <mutex>

namespace {
	struct Owner
	{
		// Properties

		/**
		 * @brief
		 *     variable used to wait for, or signal, a condition
		 *     upon which that the owner might be waiting.
		 */
		std::condition_variable_any condition;

		/**
		 * @brief
		 *     This is used to synchronize access to owner objects.
		 */
		std::mutex mutex;
		
		/**
		 * @brief
		 *     This is all the connections that have been established
		 *     between the current server and remote-clients.
		 */
		std::vector<std::shared_ptr<HTTP::Connection>> connections;

		/**
		 * @brief
		 *     This is the data received from a connection-oriented
		 *     stream.
		 */
		std::vector<uint8_t> dataReceived;

		// Methods
		
		/**
		 * @brief
		 *     This is a callback function to be called every time
		 *     a new client tries to connect to our server.
		 * 
		 * @param[in] connection
		 *     This represents the connection to the server.
		 */
		void connectionDelegate(std::shared_ptr<HTTP::Connection> connection)
		{
			std::lock_guard<decltype(mutex)> lock(mutex);
			connections.push_back(connection);
			connection->setDataReceivedDelegate(
				[this](std::vector<uint8_t> data)
				{
					receivingMessageDelegate(data);
				}
			);
			condition.notify_all();
		}

		/**
		 * @brief
		 *     This is a callback to be issued whenever more data
		 *     is received from the peer of the connection.
		 * 
		 * @param[in] message
		 *     This contains the data received from the peer of the
		 *     connection.
		 */
		void receivingMessageDelegate(const std::vector<uint8_t>& message)
		{
			std::lock_guard<decltype(mutex)> lock(mutex);
			dataReceived.insert(dataReceived.end(), message.begin(), message.end());
			condition.notify_all();
		}

		/**
		 * @brief
		 *     This method waits up to a second for a connection
		 *     to be received at the server transport layer.
		 * 
		 * @return
		 *     true if successfully the server transport received
		 *     the connection, false otherwise.
		 */
		bool awaitConnection()
		{
			std::unique_lock<decltype(mutex)> lock(mutex);
			return condition.wait_for(
				lock,
				std::chrono::seconds(1),
				[this]
				{
					return !connections.empty();
				}
			);
		}

		/**
		 * @brief
		 *     This method waits up to a second for the given number
		 *     of bytes to be received from a client connected to the
		 *     the server.
		 * 
		 * @param[in] numBytes
		 *     This is the number of bytes we expect to receive.
		 * 
		 * @return
		 *     true if successfully received the given number of bytes
		 *     from a client connected to the server, false otherwise.
		 */
		bool awaitMessage(size_t numBytes)
		{
			std::unique_lock<decltype(mutex)> lock(mutex);
			return condition.wait_for(
				lock,
				std::chrono::seconds(1),
				[this, numBytes]
				{
					return (dataReceived.size() == numBytes);
				}
			);
		}
	};
}


TEST(HTTPServerNetworkTransportTests, Placeholder)
{
	ASSERT_TRUE(true);
}
