import { Dispatch, SetStateAction } from 'react';
import { BASE_URL, ENDPOINTS } from '../../../apiConfig';

export const performKnnQuery = async (
  clickedX: number,
  clickedY: number,
  dataStructure: string,
  numNearestNeighbours: number,
  setQueriedPoints: Dispatch<SetStateAction<never[]>>,
  setQueryTime: Dispatch<SetStateAction<number>>,
) => {
  try {
    const response = await fetch(`${BASE_URL}${ENDPOINTS.KNN_QUERY}`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        queryx: clickedX,
        queryy: clickedY,
        k: numNearestNeighbours,
        structure_type: dataStructure,
      }),
    });

    if (!response.ok) {
      throw new Error('Failed to perform knn query');
    }

    const data = await response.json();
    setQueriedPoints(data.points);
    setQueryTime(data.time_taken);
  } catch (error) {
    console.error('Error performing knn query:', error);
  }
};
