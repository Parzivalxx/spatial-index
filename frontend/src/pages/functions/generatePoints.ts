import { BASE_URL, ENDPOINTS } from '../../apiConfig';

const generatePoints = async (numPoints: number) => {
  const response = await fetch(`${BASE_URL}${ENDPOINTS.GENERATE_POINTS}`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ num_points: numPoints }),
  });

  if (!response.ok) {
    throw new Error('Failed to fetch points from the server');
  }

  const data = await response.json();
  return data.points;
};

export default generatePoints;
